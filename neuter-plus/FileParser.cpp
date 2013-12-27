//
//  FileParser.cpp
//  Stringer
//
//  Created by Daniel Corn on 25/12/13.
//  Copyright (c) 2013 Daniel Corn. All rights reserved.
//

#include "FileParser.h"

using namespace std;

StringDictionary FileParser::getRequiredFileIdentifiers(string filePath) {
	string line;
	smatch result;
	StringDictionary requiredFiles;
	
	filePath = basePath + filePath;
	ifstream inputFile(filePath.c_str());
	
	const regex pattern = regex("[^/]*require\\('(.*)'\\);", std::regex_constants::icase);
	
	if (inputFile.is_open()) {
		while (getline (inputFile, line)) {
			if (regex_match(line, result, pattern)) {
				requiredFiles[result[1]] = result[0];
			}
		}
		inputFile.close();
	}
	return requiredFiles;
}

string FileParser::findAndReplaceInString(std::string &s, std::string search, std::string replace) {
	if (s.empty()) {
		return "";
	}
	for(size_t pos = 0; ; pos += replace.length()) {
        pos = s.find(search, pos);
        if (pos == string::npos) break;
		
        s.erase(pos, search.length());
        s.insert(pos, replace);
    }
	return s;
}

string FileParser::combineFilesRecursive(string rootFile) {
	string rootFilePath = rootFile;
	string mergedSubRequiredFileContent = "";
	StringDictionary requiredFileIdentifiers = getRequiredFileIdentifiers(rootFile);
	string rootFileContents;
	
	if (rootFilePath.substr(0, 1) != "/") {
		rootFilePath = basePath + rootFilePath;
	}
	rootFileContents = getFileContents(rootFilePath);
	
	for (StringDictionary::iterator it = requiredFileIdentifiers.begin(); it != requiredFileIdentifiers.end(); ++it) {
		string fileIdentifier = it->first;
		string fileIncludeCode = it->second;
		
		for (string filePath : resolveFileIdentifier(fileIdentifier)) {
			mergedSubRequiredFileContent = mergedSubRequiredFileContent
			+ wrapBefore
			+ "/*" + findAndReplaceInString(fileIncludeCode, "/", "\\/") + "// */"
			+ combineFilesRecursive(filePath)
			+ wrapAfter;
		}
		
#if CUNDD_DEBUG
		cout << "--------------------------------------------------------------------" << endl;
		cout << "File contents:" << endl;
		cout << rootFileContents << endl << endl;
		
		cout << "--------------------------------------------------------------------" << endl;
		cout << "Merged contents:" << endl;
		cout << mergedSubRequiredFileContent << endl << endl;
#endif
		
		rootFileContents = findAndReplaceInString(rootFileContents, fileIncludeCode, mergedSubRequiredFileContent);
		
#if CUNDD_DEBUG
		cout << "--------------------------------------------------------------------" << endl;
		cout << "New root file contents after replacing " << fileIdentifier << ":" << endl;
		cout << rootFileContents << endl << endl;
		cout << "--------------------------------------------------------------------" << endl;
#endif
	}
	return rootFileContents;
}

string FileParser::getFileContents(const string& filePath) {
	ifstream inputStream = ifstream(filePath, ios_base::in);
	stringstream fileContentsStream;
	if (!inputStream.good()) {
		throw FileNotFoundException("File '" + filePath + "' not found");
	}
    fileContentsStream << inputStream.rdbuf();
    return fileContentsStream.str();
}

bool FileParser::fileExists(const string& filePath) {
	struct stat buffer;
	return (stat (filePath.c_str(), &buffer) == 0);
}

vector<string> FileParser::resolveFileIdentifier(string fileIdentifier) {
	string filePath = basePath + fileIdentifier;
	if (fileExists(filePath)) {
		return vector<string>{filePath};
	}
	filePath += ".js";
	if (fileExists(filePath)) {
		return vector<string>{filePath};
	}
	if (fileIdentifier.find("*") != string::npos) {
		return resolveFileIdentifierPattern(fileIdentifier);
	}
	
	return {};
	throw FileNotFoundException("File with identifier '" + fileIdentifier + "' not found");
}

vector<string> FileParser::resolveFileIdentifierPattern(string fileIdentifier) {
	vector<string> filePaths;
	string relativePath;
	size_t basePathLength = basePath.length();
	glob_t glob_result;
	glob((basePath + fileIdentifier).c_str(), GLOB_TILDE, NULL, &glob_result);
	
	for (unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
		relativePath = string(glob_result.gl_pathv[i]);
		relativePath = relativePath.substr(basePathLength);
		filePaths.push_back(relativePath);
	}
	globfree(&glob_result);
	return filePaths;
}

void FileParser::setBasePath(string newBasePath) {
	if (newBasePath.length() && newBasePath.substr(newBasePath.length() - 1) != "/") {
		newBasePath += "/";
	}
	basePath = newBasePath;
}

void FileParser::setWrapBefore(string newWrap) {
	wrapBefore = newWrap;
}
void FileParser::setWrapAfter(string newWrap) {
	wrapAfter = newWrap;
}

