#include "errors.h"

ConfigError::ConfigError(const char* msg)
		: logic_error(msg) {
}

SqlError::SqlError(const char* msg)
		: runtime_error(msg) {
}

UnsupportedDatabaseError::UnsupportedDatabaseError(const char* msg)
		: logic_error(msg) {
}
