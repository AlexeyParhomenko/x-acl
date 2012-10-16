/*
 * Parse.cpp
 *
 *  Created on: Oct 7, 2012
 *      Author: alexey
 */

#include "Parse.h"
#include <algorithm>

namespace alex {
namespace acl {

/**
 * Конструктор
 */
Parse::Parse() {
	file_     = NULL;
	simulate_ = false;
}

/**
 * Деструктор
 */
Parse::~Parse() {

	if (file_ != NULL) {

		if (file_->is_open()) {
			file_->close();
		}

		delete file_;

	}

	if (groups_.size() > 1) {

		std::map<std::string, Group *>::iterator it;

		for (it = groups_.begin(); it != groups_.end(); it++) {
			delete it->second->getRules();
			delete it->second;
		}

	}

	groups_.clear();

}

/**
 * Возвращает конфигурационный файл
 */
std::ifstream *
Parse::getFile() {
	return file_;
}

/**
 * Возвращает группы / секции настроек
 */
std::map<std::string, Group *>
Parse::getGroups() const {
	return groups_;
}

/**
 * Возвращает необходимо ли только проверить файл без загрузки данных
 */
bool
Parse::isSimulate() {
	return simulate_;
}

/**
 * Загружает конфигурационный файл
 */
void Parse::load() throw (ParseException) {

	if (!getFile()->is_open()) {
		throw ParseException("Can't open configuration file.");
	}

	Group * group = NULL;
	std::string name, extend, line, raw;
	std::size_t pos;

	// Парсим файл
	while (getFile()->good()) {

		line.erase();
		getline(*getFile(), line);

		line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

		// Отрезаем комментарии в строке
		if ((pos = line.find("#")) != std::string::npos) {
			line = line.substr(0, pos);
		}

		if ((pos = line.find("//")) != std::string::npos) {
			line = line.substr(0, pos);
		}

		// Вырезаем ; в конце
		if ((pos = line.find_last_of(";")) != std::string::npos) {
			line = line.substr(0, pos);
		}

		// Читаем роли
		if (line.substr(0, 1) == "[") {

			if ((pos = line.find("]")) == std::string::npos) {
				continue;
			}

			name  = line.substr(1, pos - 1);
			extend.clear();

			// Если роль должна наследоваться
			if ((pos = name.find(":")) != std::string::npos) {

				extend  = name.substr(pos + 1, name.length());
				name    = name.substr(0, pos);

				if (groups_.count(extend) < 1) {

					std::string exception;

					exception
						.append("Group [")
						.append(extend)
						.append("] not found. ")
						.append("Maybe it not define or defined below group [")
						.append(name)
						.append("] ?");

					throw ParseException(exception);

				}

			}

			if (groups_.count(name) == 0) {

				group = new Group();
				groups_[name] = group;

			}
			else {
				group = groups_.at(name);
			}

			group->setName(name);

			if (!extend.empty()) {
				// Устанавливаем базовый набор правил от предыдущей роли
				group->setRules(new Rules(*groups_[extend]->getRules()));
			}

			continue;
		}

		// Читаем правила
		if (line.empty()) {
			continue;
		}

		if (group == NULL) {
			continue;
		}

		if (group->getRules() == NULL) {
			group->setRules(new Rules());
		}

		group->getRules()->addRule(line);

	}

	getFile()->close();

}

/**
 * Устанавливает конфигурационный файл
 */
void
Parse::setFile(std::ifstream * file) {
	file_ = file;
}

/**
 * Устанавливает необходимо ли только проверить файл без загрузки данных
 */
void
Parse::setSimulate(bool simulate) {
	simulate_ = simulate;
}

} /* namespace acl */
} /* namespace alex */
