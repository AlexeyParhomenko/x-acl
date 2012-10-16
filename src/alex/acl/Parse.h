/*
 * Parse.h
 *
 *  Created on: Oct 7, 2012
 *      Author: alexey
 */

#ifndef PARSE_H_
#define PARSE_H_

#include <fstream>
#include <string>
#include <map>
#include <alex/acl/Group.h>
#include <alex/acl/ParseException.h>

namespace alex {
namespace acl {

class Parse {
public:

	Parse();
	virtual ~Parse();

	/**
	 * Возвращает необходимо ли только проверить файл без загрузки данных
	 */
	bool isSimulate();

	/**
	 * Возвращает файл
	 */
	std::ifstream * getFile();

	/**
	 * Возвращает группы / секции настроек
	 */
	std::map<std::string, Group *> getGroups() const;

	/**
	 * Парсит файл и возвращает группы
	 */
	void load() throw (ParseException);

	/**
	 * Устанавливает конфигурационный файл
	 */
	void setFile(std::ifstream * file);

	/**
	 * Устанавливает необходимо ли только проверить файл без загрузки данных
	 */
	void setSimulate(bool simulate);

protected:

	std::ifstream * file_;

	/**
	 * Секции / группы настроек
	 */
	std::map<std::string, Group *> groups_;

	bool simulate_;

};

} /* namespace acl */
} /* namespace alex */
#endif /* PARSE_H_ */
