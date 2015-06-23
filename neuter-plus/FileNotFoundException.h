//
//  FileNotFoundException.h
//  Stringer
//
//  Created by Daniel Corn on 26/12/13.
//  Copyright (c) 2013 Daniel Corn. All rights reserved.
//

#ifndef __Stringer__FileNotFoundException__
#define __Stringer__FileNotFoundException__

#include <iostream>
#include "Exception.h"

using namespace Cundd;

namespace Cundd {
class FileNotFoundException : public Exception {
public:
    FileNotFoundException(const std::string& exceptionMessage)
        : Exception(exceptionMessage){};
    //public:
    //	FileNotFoundException(const string&) {}
    //	FileNotFoundException(const char*) {}
};
}

#endif /* defined(__Stringer__FileNotFoundException__) */
