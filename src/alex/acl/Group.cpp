/*
 * Group.cpp
 *
 *  Created on: Oct 7, 2012
 *      Author: alexey
 */

#include "Group.h"

namespace alex {
namespace acl {

/**
 * Конструктор
 */
Group::Group() {
	rules_ = NULL;
}

/**
 * Деструктор
 */
Group::~Group() {
	name_.erase();
}

/**
 * Возвращает название группы
 */
std::string
Group::getName() {
	return name_;
}

/**
 * Возвращает правила
 */
Rules *
Group::getRules() {
	return rules_;
}

/**
 * Устанавливает название группы
 */
void
Group::setName(std::string name) {
	name_ = name;
}

/**
 * Устанавливает правила доступа
 */
void
Group::setRules(Rules * rules) {
	rules_ = rules;
}

} /* namespace acl */
} /* namespace alex */
