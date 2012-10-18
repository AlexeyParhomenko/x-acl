/*
 * Rule.cpp
 *
 *  Created on: Oct 7, 2012
 *      Author: alexey
 */

#include "Rule.h"

namespace alex {
namespace acl {

Rule::Rule() {
	allow_ = false;
}

Rule::~Rule() {
	rule_.clear();
}

/**
 * Возвращает правило
 */
std::vector<unsigned long>
Rule::get() {
	return rule_;
}

/**
 * Разрешено ли?
 */
bool
Rule::isAllow() {
	return allow_;
}

/**
 * Устанавливает правило
 */
void
Rule::set(std::vector<unsigned long> rule) {
	rule_ = rule;
}

/**
 * Устанавливает доступ
 */
void
Rule::setAllow(bool allow) {
	allow_ = allow;
}

} /* namespace acl */
} /* namespace alex */
