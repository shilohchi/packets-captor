#ifndef ERRORS_H_
#define ERRORS_H_

#include <stdexcept>

using namespace std;

class ConfigError : public logic_error {
public:
	ConfigError(const char* msg);
};

class SqlError : public runtime_error {
public:
	SqlError(const char* msg);
};

class UnsupportedDatabaseError : public logic_error {
public:
	UnsupportedDatabaseError(const char* msg);
};
#endif
