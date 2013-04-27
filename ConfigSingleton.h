#ifndef CONFIGSINGLETON_H_
#define CONFIGSINGLETON_H_

#include <map>
#include <string>

using namespace std;

class ConfigSingleton {
private:
	static multimap<string, string>* config;
	ConfigSingleton();

public:
	static multimap<string, string>* getConfig();
};

#endif
