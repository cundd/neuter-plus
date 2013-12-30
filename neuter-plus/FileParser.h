//
//  FileParser.h
//  Stringer
//
//  Created by Daniel Corn on 25/12/13.
//  Copyright (c) 2013 Daniel Corn. All rights reserved.
//

#ifndef __Stringer__FileParser__
#define __Stringer__FileParser__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <regex>
#include <sys/stat.h>
#include <glob.h>


#include "FileNotFoundException.h"
#include "Core.h"

using namespace std;

namespace Cundd {
	typedef map<string, vector<string>> FilesMap;
	typedef map<string, string> StringDictionary;
	
	class FileParser : Core {
	protected:
		string basePath;
		string wrapBefore = "(function() {";
		string wrapAfter = "})()";
		string separator = "\n\n";

		void pad() {
			cout << string((int)(combineFilesRecursiveDepth * 4), ' ');
		}

		static int combineFilesRecursiveDepth;

	public:
		string combineFilesRecursive(string rootFile);
		void setBasePath(string newBasePath);
		void setWrapBefore(string newWrap);
		void setWrapAfter(string newWrap);
		void setSeparator(const string &separator);

		StringDictionary getRequiredFileIdentifiers(string filePath);
		vector<string> resolveFileIdentifier(string fileIdentifier);
		vector<string> resolveFileIdentifierPattern(string fileIdentifier);
		string getFileContents(const string& filePath);
		string findAndReplaceInString(std::string input, std::string search, std::string replace);
		bool fileExists(const string& filePath);
	};
}

#endif /* defined(__Stringer__FileParser__) */
