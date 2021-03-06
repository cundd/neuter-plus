//
//  FileParser.cpp
//  Stringer
//
//  Created by Daniel Corn on 25/12/13.
//  Copyright (c) 2013 Daniel Corn. All rights reserved.
//

#include "FileParser.h"

using namespace std;

int FileParser::combineFilesRecursiveDepth = 0;

StringDictionary FileParser::getRequiredFileIdentifiers(string filePath)
{
    string line;
    smatch result;
    StringDictionary requiredFiles;

    if (filePath.substr(0, 1) != "/") {
        filePath = basePath + filePath;
    }
    ifstream inputFile(filePath.c_str());

    const regex pattern = regex("^\\s*require\\(['\"]([^'\"]+)['\"]\\);", std::regex_constants::icase);

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            if (regex_match(line, result, pattern)) {

                if (verbose) {
                    //					pad(); cout << "====================================================================" << endl;
                    pad();
                    cout << "Matching: " << result[0] << endl;
                }

                requiredFiles[result[1]] = result[0];
            }
        }
        inputFile.close();
    }
    else {
        throw FileNotFoundException("Could not open file '" + filePath + "'");
    }
    return requiredFiles;
}

string FileParser::combineFilesRecursive(string rootFile)
{
    string rootFilePath = rootFile;
    string mergedSubRequiredFileContent = "";
    string rootFileContents;

    if (verbose) {
        pad();
        cout << "====================================================================" << endl;
        pad();
        cout << "Analyse file: " << rootFile << endl;
    }

    StringDictionary requiredFileIdentifiers = getRequiredFileIdentifiers(rootFile);

    if (rootFilePath.substr(0, 1) != "/") {
        rootFilePath = basePath + rootFilePath;
    }
    rootFileContents = getFileContents(rootFilePath);

    for (StringDictionary::iterator it = requiredFileIdentifiers.begin(); it != requiredFileIdentifiers.end(); ++it) {
        string fileIdentifier = it->first;
        string fileIncludeCode = it->second;
        bool couldNotResolveAnyFiles = TRUE;
        mergedSubRequiredFileContent = separator;

        for (string filePath : resolveFileIdentifier(fileIdentifier)) {
            couldNotResolveAnyFiles = FALSE;
            if (find(loadedFiles.begin(), loadedFiles.end(), filePath) != loadedFiles.end()) {
#if CUNDD_DEBUG
                pad();
                cout << "====================================================================" << endl;
                pad();
                cout << "--------------------------------------------------------------------" << endl;
                pad();
                cout << "Skip " << filePath << " - already loaded" << endl;
#endif
                continue;
            }
            loadedFiles.push_back(filePath);

            ++combineFilesRecursiveDepth;
            string subRequiredFileContent = combineFilesRecursive(filePath);
            --combineFilesRecursiveDepth;

#if CUNDD_DEBUG
            pad();
            cout << "--------------------------------------------------------------------" << endl;
            pad();
            cout << subRequiredFileContent << endl
                 << endl;
            pad();
            cout << "--------------------------------------------------------------------" << endl;
#endif

            mergedSubRequiredFileContent = mergedSubRequiredFileContent + subRequiredFileContent + separator;
        }

#if CUNDD_DEBUG
        pad();
        cout << "--------------------------------------------------------------------" << endl;
        pad();
        cout << "File contents:" << endl;
        pad();
        cout << rootFileContents << endl
             << endl;
#endif

#if CUNDD_DEBUG
        pad();
        cout << "--------------------------------------------------------------------" << endl;
        pad();
        cout << "Merged contents:" << endl;
        pad();
        cout << mergedSubRequiredFileContent << endl
             << endl;

        pad();
        cout << "--------------------------------------------------------------------" << endl;
        pad();
        cout << "replace " << fileIncludeCode << endl;
#endif

        if (couldNotResolveAnyFiles == FALSE || !keepUnresolvedIncludes) {
            mergedSubRequiredFileContent = wrapBefore
                + "/*" + StringUtility::findAndReplaceInString(fileIncludeCode, "/", "\\/") + "// */"
                + mergedSubRequiredFileContent
                + wrapAfter
                + separator;
            rootFileContents = StringUtility::findAndReplaceInString(rootFileContents, fileIncludeCode, mergedSubRequiredFileContent);
        }

#if CUNDD_DEBUG
        pad();
        cout << "--------------------------------------------------------------------" << endl;
        pad();
        cout << "New root file contents after replacing " << fileIncludeCode << ":" << endl;
        pad();
        cout << rootFileContents << endl
             << endl;
        pad();
        cout << "--------------------------------------------------------------------" << endl;
#endif
    }
    return rootFileContents;
}

string FileParser::getFileContents(const string& filePath)
{
    ifstream inputStream = ifstream(filePath, ios_base::in);
    stringstream fileContentsStream;
    if (!inputStream.good()) {
        throw FileNotFoundException(("File '" + filePath + "' not found"));
    }
    fileContentsStream << inputStream.rdbuf();
    return fileContentsStream.str();
}

bool FileParser::fileExists(const string& filePath)
{
    struct stat buffer;
    return (stat(filePath.c_str(), &buffer) == 0);
}

vector<string> FileParser::resolveFileIdentifier(string fileIdentifier)
{
    string filePath = basePath + fileIdentifier;
    vector<string> filePaths;

    if (fileExists(filePath)) {
        filePaths.push_back(filePath);
        return filePaths;
    }
    filePath += ".js";
    if (fileExists(filePath)) {
        filePaths.push_back(filePath);
        return filePaths;
    }
    if (fileIdentifier.find("*") != string::npos) {
        return resolveFileIdentifierPattern(fileIdentifier);
    }

    if (verbose)
        pad();
    cerr << "File with identifier '" + fileIdentifier + "' not found" << endl;

    return {};
    throw FileNotFoundException("File with identifier '" + fileIdentifier + "' not found");
}

vector<string> FileParser::resolveFileIdentifierPattern(string fileIdentifier)
{
    vector<string> filePaths;
    string relativePath;
    size_t basePathLength = basePath.length();
    glob_t glob_result;
    glob((basePath + fileIdentifier + ".js").c_str(), GLOB_TILDE, NULL, &glob_result);

    for (unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
        relativePath = string(glob_result.gl_pathv[i]);
        relativePath = relativePath.substr(basePathLength);
        filePaths.push_back(relativePath);
    }
    globfree(&glob_result);
    return filePaths;
}

void FileParser::setBasePath(string newBasePath)
{
    if (newBasePath.length() && newBasePath.substr(newBasePath.length() - 1) != "/") {
        newBasePath += "/";
    }
    basePath = newBasePath;
}

void FileParser::setWrapBefore(string newWrap)
{
    wrapBefore = newWrap;
}

void FileParser::setWrapAfter(string newWrap)
{
    wrapAfter = newWrap;
}

void FileParser::setSeparator(const string& newSeparator)
{
    separator = newSeparator;
}

void FileParser::setVerbose(bool flag)
{
    verbose = flag;
}

void FileParser::setKeepUnresolvedIncludes(bool flag)
{
    keepUnresolvedIncludes = flag;
}
