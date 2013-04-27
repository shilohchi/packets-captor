#include "ConfigSingleton.h"
#include "errors.h"
#include <map>
#include <string>
#include "tinyxpath/tinyxml.h"
#include "tinyxpath/xpath_processor.h"

#include <iostream>
using namespace std;

using namespace std;
using namespace TinyXPath;

ConfigSingleton::ConfigSingleton() {}

multimap<string, string>* ConfigSingleton::config = NULL;

multimap<string, string>* ConfigSingleton::getConfig() {
	if (ConfigSingleton::config == NULL) {

	
		ConfigSingleton::config = new multimap<string, string>();
		const char* filename = "config.xml";
		TiXmlDocument doc(filename);
		if (!doc.LoadFile()) {
			
			throw ConfigError("Cannot open config.xml!");
		}
		
		TiXmlElement* root = doc.RootElement();
		
	
		xpath_processor* xproc = new xpath_processor(root, "/app/network-interface");
		unsigned int num = xproc->u_compute_xpath_node_set();
		if (num != 1) {
			throw ConfigError("There must be one and only one network interface name!");
		}
		TiXmlElement* e = (TiXmlElement*) (xproc->XNp_get_xpath_node(0));
		config->insert(make_pair("network-interface", e->GetText()));
		delete xproc;

	
		xproc = new xpath_processor(root, "/app/database/host");
		num = xproc->u_compute_xpath_node_set();
		if (num != 1) {
			throw ConfigError("Requires (only) one host for databse.");
		}
		e = (TiXmlElement*) (xproc->XNp_get_xpath_node(0));
		config->insert(make_pair("database-host", e->GetText()));
		delete xproc;
		
		xproc = new xpath_processor(root, "/app/database/user");
		num = xproc->u_compute_xpath_node_set();
		if (num != 1) {
			throw ConfigError("Requires (only) one user for database.");
		}
		e = (TiXmlElement*) (xproc->XNp_get_xpath_node(0));
		config->insert(make_pair("database-user", e->GetText()));
		delete xproc;

		xproc = new xpath_processor(root, "/app/database/password");
		num = xproc->u_compute_xpath_node_set();
		if (num != 1) {
			throw ConfigError("Requires (only) one password for database.");
		}
		e = (TiXmlElement*) (xproc->XNp_get_xpath_node(0));
		config->insert(make_pair("database-password", e->GetText()));
		delete xproc;

		xproc = new xpath_processor(root, "/app/database/name");
		num = xproc->u_compute_xpath_node_set();
		if (num != 1) {
			throw ConfigError("Requires (only) one database name.");
		}
		e = (TiXmlElement*) (xproc->XNp_get_xpath_node(0));
		config->insert(make_pair("database-name", e->GetText()));
		delete xproc;
		
		xproc = new xpath_processor(root, "/app/low-level-filters/rule");
		num = xproc->u_compute_xpath_node_set();
		for (int i = 0; i < num; i++) {
			e = (TiXmlElement*) (xproc->XNp_get_xpath_node(i));
			config->insert(make_pair("low-level-filter", e->GetText()));
		}
		delete xproc;

		xproc = new xpath_processor(root, "/app/application-layer-filters/rule");
		num = xproc->u_compute_xpath_node_set();
		for (int i = 0; i < num; i++) {
			e = (TiXmlElement*) (xproc->XNp_get_xpath_node(i));
			config->insert(make_pair("application-layer-filter", e->GetText()));
		}
		delete xproc;
	}
	return ConfigSingleton::config;
}
