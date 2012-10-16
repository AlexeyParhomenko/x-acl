/*
 * ParseException.h
 *
 *  Created on: Oct 7, 2012
 *      Author: alexey
 */

#ifndef PARSEEXCEPTION_H_
#define PARSEEXCEPTION_H_

#include <exception>
#include <string>

namespace alex {
namespace acl {

class ParseException {
public:

	ParseException() { what_ = 0; };
	ParseException(std::string s);
	ParseException(std::string s, int e);

	const char * what() const;

protected:

	std::string whatString_;
	int  what_;

};

} /* namespace acl */
} /* namespace alex */
#endif /* PARSEEXCEPTION_H_ */
