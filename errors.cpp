#include "errors.h"

ConfigError::ConfigError(const char* msg)
		: logic_error(msg) {
}

