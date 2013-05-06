#ifndef CXXPCAP_UTILS_H_
#define CXXPCAP_UTILS_H_
#include <string>
#include <stdexcept>

namespace cxxpcap {
enum class Protocol {
	Unknown,
	ARP,
	Ethernet,
	RARP,
	INET,
	IP,
	TCP,
	UDP,
	HTTP
};

class PcapError : public std::runtime_error {
public:
	PcapError(const char* msg) :
			std::runtime_error(msg) {
	}
};

class PacketError : public PcapError {
public:
	PacketError(const char* msg) :
			PcapError(msg) {
	}
};

class PcapConfigError : public PcapError {
public:
	PcapConfigError(const char* msg) :
			PcapError(msg) {
	}
};

struct NetworkInterface {
	std::string name;
	std::string description;
};

}
#endif
