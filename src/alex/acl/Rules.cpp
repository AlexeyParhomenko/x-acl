/*
 * Rules.cpp
 *
 *  Created on: Oct 7, 2012
 *      Author: alexey
 */

#include <algorithm>
#include "Rules.h"

namespace alex {
namespace acl {

/**
 * Конструктор
 */
Rules::Rules() {

}

/**
 * Копирующий конструктор
 */
Rules::Rules(const Rules& object) {

	if (object.rules_.size() > 0) {

		for (size_t i = 0; i < object.rules_.size(); i++) {
			rules_.push_back(new Rule(*(object.rules_[i])));
		}

	}

}

/**
 * Деструктор
 */
Rules::~Rules() {

	while (!rules_.empty()) {
		delete rules_.back();
		rules_.pop_back();
	}

	rules_.clear();

}

/**
 * Добавляет правило
 */
Rules &
Rules::addRule(std::string raw) {

	size_t pos   = raw.find("=");
	Rule * rule  = new Rule();
	rule->setAllow(true);

	if (pos != std::string::npos) {

		std::string access = raw.substr(pos + 1, raw.length());
		access.erase(std::remove_if(access.begin(), access.end(), isspace), access.end());

		if (access == "disallow"
				|| access == "false"
				|| access == "deny"
				|| access == "0") {
			rule->setAllow(false);
		}

		raw = raw.substr(0, pos);
	}

	raw.erase(std::remove_if(raw.begin(), raw.end(), isspace), raw.end());

	if (raw.empty()) {
		return *this;
	}

	rule->set(convertToMask_(raw));

	if (rule->isAllow()) {
		rules_.push_back(rule);
	}
	else {
		rules_.insert(rules_.begin(), rule);
	}

	return *this;

}

/**
 * Конвертируем набор символов в их int значения
 */
std::vector <int>
Rules::convertToMask_(std::string rule) {

	std::vector <int> rules;

	unsigned int i;
	int chr, mask = 0;

	for (i = 0; i < rule.length(); i++) {

		chr = (int) rule.at(i);

		switch (chr) {

			// Символ двоеточие
			case 58:

				rules.push_back(mask);
				mask = 0;

				break;

			default:

				mask += chr;
				break;

		}

	}

	// Последний элемент правила
	if (mask > 0) {
		rules.push_back(mask);
	}

	return rules;
}

/**
 * Проверяем разрешен ли доступ
 */

bool
Rules::isAllow(std::string resource) {
	return this->isAllow(resource, 0, 1);
}

bool
Rules::isAllow(std::string resource, unsigned long idUser, unsigned long idOwner) {

	if (resource.size() < 1 || resource.empty()) {
		return false;
	}

	// Конвертируем в маску
	std::vector <int> mask = convertToMask_(resource);

	unsigned int i, currentMask, ruleSize;
	std::vector<Rule *>::iterator it;
	Rule * rule;

	// Перебираем правила
	for (it = rules_.begin(); it != rules_.end(); it++) {

		rule = (*it);

		currentMask = 0;
		ruleSize    = rule->get().size(); // Если правило заканчивается на * - мы подменяем размер

		// Ищем совпадение с маской
		for (i = 0; i < ruleSize; i++) {

			if (mask.size() == currentMask) {
				break;
			}

			if (currentMask >= 0 && i != currentMask) {
				break;
			}

			switch (rule->get().at(i)) {

				// 42 - символ * - заменяет любую строку
				case 42:

					/*
					 * Если есть совпадение и правило заканчивается на *
					 * очевидно, что дальше искать смысла нет.
					 *
					 * Например:
					 *
					 *   правило - view:*
					 *   маска   - view:wall:comment
					 *
					 * Очевидно, что в данном случае мы уже все разрешили
					 */

					if (i + 1 == rule->get().size()) {

						currentMask = mask.size();
						ruleSize    = currentMask;

						continue;

					}

					currentMask++;

				break;

				// 94 - символ ^ - разрешает только если idUser == idOwner
				case 94:

					if (idOwner != idUser) {
						continue;
					}

					currentMask++;

				break;

				default:

					if (mask[i] == rule->get().at(i)) {

						currentMask++;
						continue;

					}

					break;
			}

		}

		if (currentMask == mask.size() && currentMask == ruleSize) {
			return rule->isAllow();
		}

	}

	return false;

}

/**
 * Возвращает набор правил
 */
std::vector<Rule *>
Rules::getRules() const {
	return rules_;
}

} /* namespace acl */
} /* namespace alex */
