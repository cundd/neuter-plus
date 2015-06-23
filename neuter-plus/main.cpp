//
//  main.cpp
//  neuter-plus
//
//  Created by Daniel Corn on 27/12/13.
//  Copyright (c) 2013 cundd. All rights reserved.
//

#include <iostream>
#include "String.h"
#include "FileParser.h"

#ifndef NEUTER_VERSION
#define NEUTER_VERSION "0.1.2"
#endif

using namespace std;
using namespace Cundd;


int main(int argc, const char* argv[])
{
    bool useStandardOut = FALSE;
    string inputFilePath = "", outputFilePath = "", combinedContents;
    FileParser fileParser = FileParser();
    ofstream outputFile;

    for (int i = 1; i < argc;
         i++) { /* We will iterate over argv[] to get the parameters stored
               * inside.
                                               * Note that we're starting on 1
               * because we don't need to know the
                                               * path of the program, which is
               * stored in argv[0] */
        if (i != argc) { // Check that we haven't finished parsing already
            if (string(argv[i]) == "--input") {
                // We know the next argument *should* be the filename:
                inputFilePath = string(argv[i + 1]);
            }
            else if (string(argv[i]) == "--output") {
                outputFilePath = string(argv[i + 1]);
            }
            else if (string(argv[i]) == "--basePath") {
                fileParser.setBasePath(string(argv[i + 1]));
            }
            else if (string(argv[i]) == "--wrapBefore") {
                fileParser.setWrapBefore(string(argv[i + 1]));
            }
            else if (string(argv[i]) == "--wrapAfter") {
                fileParser.setWrapAfter(string(argv[i + 1]));
            }
            else if (string(argv[i]) == "--separator") {
                fileParser.setSeparator(string(argv[i + 1]));
            }
            else if (string(argv[i]) == "--stdout") {
                useStandardOut = TRUE;
                --i;
            }
            else if (string(argv[i]) == "--keep-unresolved-includes") {
                fileParser.setKeepUnresolvedIncludes(TRUE);
                --i;
            }
            else if (string(argv[i]) == "--verbose" || string(argv[i]) == "-v") {
                fileParser.setVerbose(TRUE);
                --i;
            }
            else if (string(argv[i]) == "--version") {
                cout << "neuter-plus " << NEUTER_VERSION;
#if DEBUG
                cout << "-dev";
#endif
                cout << endl;
                exit(0);
            }
            else {
                cout << "Not enough or invalid arguments" << endl;
                exit(1);
            }
        }
        i++;
    }

    if (inputFilePath == "") {
        cout << "Please specify the input file path ('--input')" << endl;
        exit(1);
    }
    if (outputFilePath == "" && !useStandardOut) {
        cout << "Please specify the output file path ('--output')" << endl;
        exit(1);
    }

    cout << "Try to read from file '" + inputFilePath + "'\n";
    try {
        combinedContents = fileParser.combineFilesRecursive(inputFilePath);

        if (useStandardOut) {
            cout << combinedContents;
        }
        else {
            outputFile.open(outputFilePath);
            outputFile << combinedContents;
            outputFile.close();
        }
    }
    catch (Exception e) {
        cerr << e.getMessage();
        return 1;
    }
    return 0;
}
