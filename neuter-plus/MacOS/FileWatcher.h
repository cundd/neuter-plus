//
//  FileWatcher.h
//  neuter-plus
//
//  Created by Daniel Corn on 10/01/14.
//  Copyright (c) 2014 cundd. All rights reserved.
//

#ifndef __neuter_plus__FileWatcher__
#define __neuter_plus__FileWatcher__

#include <iostream>

using namespace std;

class FileWatcher : public Core {
public:
	void watch(const string &directoryPath);
};

#endif /* defined(__neuter_plus__FileWatcher__) */
