#ifndef ERRORS_H_
#define ERRORS_H_

#include <stdexcept>

using namespace std;

class ConfigError : public logic_error {
public:
	ConfigError(const char* msg);
};

#endif
