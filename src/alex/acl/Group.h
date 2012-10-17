/*
 * Group.h
 *
 *  Created on: Oct 7, 2012
 *      Author: alexey
 */

#ifndef GROUP_H_
#define GROUP_H_

#include "alex/acl/Rules.h"

namespace alex {
namespace acl {

class Group {
public:

	Group();
	virtual ~Group();

	std::string    getName();
	Rules        * getRules();
	void          setName(std::string name);
	void          setRules(Rules * rules);


protected:

	std::string    name_;
	Rules        * rules_;

};

} /* namespace acl */
} /* namespace alex */
#endif /* GROUP_H_ */
