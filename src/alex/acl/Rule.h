/*
 * Rule.h
 *
 *  Created on: Oct 7, 2012
 *      Author: alexey
 */

#ifndef RULE_H_
#define RULE_H_

#include <string>
#include <vector>

namespace alex {
namespace acl {

class Rule {
public:

	Rule();
	virtual ~Rule();

	/**
	 * Возвращает правило
	 */
	std::vector<int> get();

	/**
	 * Разрешено ли?
	 */
	bool isAllow();

	/**
	 * Устанавливает правило
	 */
	void set(std::vector<int> rule);

	/**
	 * Устанавливает доступ
	 */
	void setAllow(bool access);


protected:

	bool allow_;
	std::vector<int> rule_;

};

} /* namespace acl */
} /* namespace alex */
#endif /* RULE_H_ */
