//
//  main.cpp
//  neuter-plus
//
//  Created by Daniel Corn on 27/12/13.
//  Copyright (c) 2013 cundd. All rights reserved.
//

#include <iostream>
#include "FileParser.h"

using namespace std;
using namespace Cundd;

int main(int argc, const char * argv[]) {
	bool useStandardOut = FALSE;
	string inputFilePath = "", outputFilePath = "",
			wrapBefore = "(function() {",
			wrapAfter = "})()",
			basePath = "",
			combinedContents;
	FileParser fileParser = FileParser();
	ofstream outputFile;

	for (int i = 1; i < argc; i++) { /* We will iterate over argv[] to get the parameters stored inside.
									  * Note that we're starting on 1 because we don't need to know the
									  * path of the program, which is stored in argv[0] */
 		if (i + 1 != argc) {// Check that we haven't finished parsing already
			if (string(argv[i]) == "--input") {
				// We know the next argument *should* be the filename:
				inputFilePath = string(argv[i + 1]);
			} else if (string(argv[i]) == "--output") {
				outputFilePath = string(argv[i + 1]);
			} else if (string(argv[i]) == "--basePath") {
				basePath = string(argv[i + 1]);
			} else if (string(argv[i]) == "--wrapBefore") {
				wrapBefore = string(argv[i + 1]);
			} else if (string(argv[i]) == "--wrapAfter") {
				wrapAfter = string(argv[i + 1]);
			} else if (string(argv[i]) == "--stdout") {
				useStandardOut = TRUE;
			} else {
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
	if (outputFilePath == "") {
		cout << "Please specify the output file path ('--output')" << endl;
		exit(1);
	}

	fileParser.setBasePath(basePath);
	fileParser.setWrapBefore(wrapBefore);
	fileParser.setWrapAfter(wrapAfter);

	cout << "Try to read from file '" + inputFilePath + "'\n";
	try {
		combinedContents = fileParser.combineFilesRecursive(inputFilePath);

		if (useStandardOut) {
			cout << combinedContents;
		} else {
			outputFile.open(outputFilePath);
			outputFile << combinedContents;
			outputFile.close();
		}
	} catch (Exception e) {
		cout << e.getMessage();
	}
	return 0;
}
