#include "cxxpcap/DatalinkInfo.h"
#include <cstdint>

using namespace std;

namespace cxxpcap {
EthernetInfo::EthernetInfo(const uint8_t* header) {
	this->header = new uint8_t[LENGTH];
	for (int i = 0; i < LENGTH; i++) {
		this->header[i] = header[i];
	}
}

EthernetInfo::~EthernetInfo() {
	delete[] header;
}

Protocol EthernetInfo::getProtocol() {
	Protocol protocol;

	switch (*((uint16_t*) header[12])) {
	case 0x0008:
		protocol =  Protocol::IP;
		break;
	case 0x0608:
		protocol = Protocol::ARP;
		break;
	case 0x3580:
		protocol = Protocol::RARP;
		break;
	default:
		protocol = Protocol::Unknown;
	}

	return protocol;
}

int Ethernet::getLength() {
	return LENGTH;
}
}
