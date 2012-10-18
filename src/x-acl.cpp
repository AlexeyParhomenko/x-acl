//============================================================================
// Name        : acl.cpp
// Author      : Alexey Parhomenko
// Version     : 0.2
//============================================================================

#include <getopt.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

#include "alex/acl/Group.h"
#include "alex/acl/Rules.h"
#include "alex/acl/Parse.h"
#include "alex/acl/ParseException.h"

using namespace alex::acl;

/**
 * Справка программы
 */
void displayHelp() {

	std::cout
		<< "   -h [ --help ]         help" << std::endl
		<< "   -c [ --config ] arg   Path to configuration file." << std::endl
		<< "   -g [ --group ] arg    Group name for check acl. For example [users]" << std::endl
		<< "   -r [ --resource ] arg Resource name for check acl. For example - add:comment" << std::endl
		<< "   -u [ --user-id ] arg  Current user ID." << std::endl
		<< "   -o [ --owner-id ] arg Resource owner." << std::endl
		<< "   -t [ --test ]         Test configuration and exit." << std::endl
		<< "   -v [ --version ]      Show version and exit" << std::endl
		<< std::endl;
}

void displayVersion() {
	std::cout << "x-acl version: 0.3" << std::endl << std::endl;
}

/**
 * Точка входа
 */
int main(int argc, char** argv) {

	struct params_t {
		const char      * config;
		const char      * group;
		const char      * resource;
		unsigned long     idUser;
		unsigned long     idOwner;
		bool               test;
		bool               version;
	} params;

	params.config     = NULL;
	params.group      = NULL;
	params.resource   = NULL;
	params.idUser     = 1;
	params.idOwner    = 0;
	params.test       = false;

	const char *optString = "c:g:r:u:o:tvh?";

	const struct option longOpts[] = {
			{ "config", required_argument, NULL, 'c' },
			{ "group", required_argument, NULL, 'g' },
			{ "resource", required_argument, NULL, 'r' },
			{ "user-id", no_argument, NULL, 'u' },
			{ "owner-id", no_argument, NULL, 'o' },
			{ "test", no_argument, NULL, 't' },
			{ "version", no_argument, NULL, 'v' },
			{ "help", no_argument, NULL, 'h' },
			{ NULL, no_argument, NULL, 0 }
	};

	int opt, longIndex;

	opt = getopt_long(argc, argv, optString, longOpts, &longIndex);

	while (opt != -1) {

		switch (opt) {

			case 'c':
				params.config   = optarg;
				break;

			case 'g':
				params.group    = optarg;
				break;

			case 'r':
				params.resource = optarg;
				break;

			case 'u':
				params.idUser   = atol(optarg);
				break;

			case 'o':
				params.idOwner  = atol(optarg);
				break;

			case 't':
				params.test     = true;
				break;

			case 'v':
				displayVersion();
				return EXIT_SUCCESS;
				break;

			case 'h':
			case '?':
				displayHelp();
				return EXIT_SUCCESS;
				break;

			/* длинная опция без короткого эквивалента */
			case 0:

				break;
		}

		opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	}

	if (argc == 1) {
		displayHelp();
		return EXIT_SUCCESS;
	}

	if (params.config == NULL) {
		std::cout << "Please, put path to configuration file -c" << std::endl;
		return EXIT_FAILURE;
	}

	if (!params.test &&
			(params.group == NULL || params.resource == NULL) ) {
		std::cout << "Please, put group -g or resource -r" << std::endl;
		return EXIT_FAILURE;
	}


	Parse * parse = NULL;

	try {

		parse = new Parse();
		parse->setSimulate(params.test);
		parse->setFile(new std::ifstream(params.config));
		parse->load();

		if (!params.test) {

			bool allow;

			if (!parse->getGroups().count(params.group)) {
				throw ParseException(
						"Group " + ( (std::string) params.group ) + " not found in configuration file.");
			}

			allow =
					parse->getGroups().at(params.group)
						->getRules()
							->isAllow(
									params.resource,
									params.idUser,
									params.idOwner);

			if (allow) {
				std::cout << "Access allow" << std::endl;
			} else {
				std::cout << "Access denied" << std::endl;
			}

		}

	} catch (ParseException &e) {
		std::cout << "Error: " << e.what() << std::endl;
	} catch (...) {
		std::cout << "Error: unknown. Please, report about this to developers. "
				<< std::endl;
	}

	if (NULL != parse) {
		delete parse;
	}

	return EXIT_SUCCESS;
}
