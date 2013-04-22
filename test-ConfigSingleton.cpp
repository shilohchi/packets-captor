#include "ConfigSingleton.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;

int __main() {

	cout<<"dfa1"<<endl;
	multimap<string, string>* config = ConfigSingleton::getConfig();

	multimap<string, string>::iterator it = config->find("network-interface");

	cout << it->second << endl;
	
	it = config->find("database-host");
	cout << it->second << endl;

	it = config->find("database-user");
	cout << it->second << endl;

	it = config->find("database-password");
	cout << it->second << endl;

	for (it = config->lower_bound("low-level-filter"); 
		it != config->upper_bound("low-level-filter");
		it++) {
			cout << "low level filter: " << it->second << endl;
	}


	for (it = config->lower_bound("application-layer-filter"); 
		it != config->upper_bound("application-layer-filter");
		it++) {
			cout << "application layer filter: " << it->second << endl;
	}
	
	return 0;
}
