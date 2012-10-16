//============================================================================
// Name        : acl.cpp
// Author      : Alexey Parhomenko
// Version     : 0.2
//============================================================================

#include <iostream>
#include <fstream>

#include <boost/program_options.hpp>

#include <alex/acl/Group.h>
#include <alex/acl/Rules.h>

#include <alex/acl/Parse.h>
#include <alex/acl/ParseException.h>

using namespace alex::acl;

/**
 * Точка входа
 */
int main (int argc, char** argv) {

	namespace po = boost::program_options;

	std::string path;

	po::options_description description("allowed options");

	description.add_options()
		("help,h", "help")
		("config,c", po::value<std::string>(&path)->default_value(path), "Path to configuration file.")
		("group,g", po::value<std::string>(), "Group name for check acl. For example [users]")
		("resource,r", po::value<std::string>(), "Resource name for check acl. For example - add:comment")
		("user-id,u", po::value<unsigned long>(), "Current user ID.")
		("owner-id,o", po::value<unsigned long>(), "Resource owner.")
		("test,t", "Test configuration and exit.")
		("version,v", "Show version and exit");

	po::variables_map options;

	try {
		po::store(po::parse_command_line(argc, argv, description), options);
	}
	catch (const std::exception& e) {
		std::cout << "command line error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	if (options.count("help") || options.size() == 1) {
		std::cout << description << std::endl;
		return EXIT_SUCCESS;
	}

	if (options.count("version")) {
		std::cout << "0.2" << std::endl;
		return EXIT_SUCCESS;
	}

	Parse * parse = NULL;

	try {

		if (options.count("config")) {
			path = options["config"].as<std::string>();
		}

		parse = new Parse();

		if (options.count("test")) {
			parse->setSimulate(true);
		}

		parse->setFile(new std::ifstream (path.c_str()));
		parse->load();

		if (options.count("group") && options.count("resource") && !options.count("simulate")) {

			std::string
				group      = options["group"].as<std::string>(),
				resource   = options["resource"].as<std::string>();

			bool allow;

			if (!parse->getGroups().count(group)) {
				throw ParseException("Group " + group + " not found in configuration file.");
			}

			if (options.count("user-id") && options.count("owner-id")) {

				allow = parse->getGroups().at(group)
						->getRules()
						->isAllow(
								resource,
								options["user-id"].as<unsigned long>(),
								options["owner-id"].as<unsigned long>());

			}
			else {
				allow = parse->getGroups().at(group)->getRules()->isAllow(resource, 0, 1);
			}

			if (allow) {
				std::cout << "Access allow" << std::endl;
			}
			else {
				std::cout << "Access denied" << std::endl;
			}

		}
		else if (!options.count("simulate")) {
			std::cout << "Please, put group -g or resource -r" << std::endl;
		}

	}
	catch (ParseException &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Error: unknown. Please, report about this to developers. " << std::endl;
	}

	if (NULL != parse) {
		delete parse;
	}

	return EXIT_SUCCESS;
}
