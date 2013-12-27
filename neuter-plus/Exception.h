//
//  Exception.h
//  Stringer
//
//  Created by Daniel Corn on 26/12/13.
//  Copyright (c) 2013 Daniel Corn. All rights reserved.
//

#ifndef __Stringer__Exception__
#define __Stringer__Exception__

#include <iostream>

using namespace std;

namespace Cundd {
	class Exception : public exception {
	protected:
		string message;
	public:
		Exception(const string&);
		string getMessage();
	};
}

#endif /* defined(__Stringer__Exception__) */
