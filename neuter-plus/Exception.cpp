//
//  Exception.cpp
//  Stringer
//
//  Created by Daniel Corn on 26/12/13.
//  Copyright (c) 2013 Daniel Corn. All rights reserved.
//

#include "Exception.h"


namespace Cundd {	
	Exception::Exception(const string& exceptionMessage) {
		message = exceptionMessage;
	}
	string Exception::getMessage() {
		return message;
	}
}