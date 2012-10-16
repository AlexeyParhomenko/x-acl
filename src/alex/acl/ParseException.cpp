/*
 * ParseException.cpp
 *
 *  Created on: Oct 7, 2012
 *      Author: alexey
 */

#include "ParseException.h"
#include <cstring>

namespace alex {
namespace acl {

ParseException::ParseException(std::string s) {
	whatString_  = s;
}

ParseException::ParseException(std::string s, int e) {
	whatString_  = s;
	what_        = e;
}

const char *
ParseException::what() const {
	return whatString_.c_str();
}

} /* namespace acl */
} /* namespace alex */
