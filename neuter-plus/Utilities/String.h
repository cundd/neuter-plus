//
// Created by Daniel Corn on 30/12/13.
// Copyright (c) 2013 cundd. All rights reserved.
//

#ifndef __String_H_
#define __String_H_

#include <iostream>

using namespace std;

namespace Cundd {
class StringUtility {
public:
    static std::string findAndReplaceInString(std::string input, std::string search, std::string replace)
    {
        if (input.empty()) {
            return "";
        }
        for (size_t pos = 0;; pos += replace.length()) {
            pos = input.find(search, pos);
            if (pos == string::npos)
                break;

            input.erase(pos, search.length());
            input.insert(pos, replace);
        }
        return input;
    }
};
}

#endif //__String_H_
