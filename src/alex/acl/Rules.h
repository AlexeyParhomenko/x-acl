/*
 * Rules.h
 *
 *  Created on: Oct 7, 2012
 *      Author: alexey
 */

#ifndef RULES_H_
#define RULES_H_

#include <string>
#include <map>
#include <vector>

#include "alex/acl/Rule.h"

namespace alex {
namespace acl {

class Rules {
public:

	Rules();
	virtual ~Rules();

	/**
	 * Копирующий конструктор
	 */
	Rules(const Rules& object);

	Rules & addRule(std::string rule);
	bool isAllow(std::string resource);
	bool isAllow(std::string resource, unsigned long idUser, unsigned long idOwner);

	/**
	 * Возвращает набор правил
	 */
	std::vector<Rule *> getRules() const;

protected:

	std::vector<Rule *> rules_;
	std::vector <int> convertToMask_(std::string rule);

};

} /* namespace acl */
} /* namespace alex */
#endif /* RULES_H_ */
