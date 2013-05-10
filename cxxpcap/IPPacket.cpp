#include <glog/logging.h>
#include "cxxpcap/IPPacket.h"
#include <string>
#include <cstdint>

using namespace std;

namespace cxxpcap {
bool IPPacket::isValid(const uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) {
	if (!InetPacket::isValid(raw_data, raw_data_length, datalink_protocol)) {
		return false;
	}
	InetPacket inetpkt(raw_data, raw_data_length, datalink_protocol);
	if (inetpkt.getDatalinkProtocol() != Protocol::IP) {
		return false;
	}
	if (inetpkt.datalink_data_end() < inetpkt.datalink_data_begin() + 20) {
		return false;
	}
	int len = int(*inetpkt.datalink_data_begin() & 0xf) * 4;
	if (inetpkt.datalink_data_end() < inetpkt.datalink_data_begin() + len) {
		return false;
	}
	return true;
}


IPPacket::IPPacket(const uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) :
		IPPacket(raw_data_length, {0, 0}, raw_data, raw_data_length, datalink_protocol) {
}

IPPacket::IPPacket(int length, timeval timestamp, const uint8_t* raw_data,
		int raw_data_length, Protocol datalink_protocol) :
		InetPacket(length, timestamp, raw_data, raw_data_length, datalink_protocol) {
	this->ip_header = this->datalink_data;
	this->ip_data = this->datalink_data + getIPHeaderLength();
}	


IPPacket::IPPacket(const IPPacket& p) :
		InetPacket(p) {
}

Protocol IPPacket::getIPProtocol() const {
	Protocol protocol;
	switch (*(ip_header + 9)) {
	case 0x11:
		protocol = Protocol::UDP;
		break;
	case 0x06:
		protocol = Protocol::TCP;
		break;
	default:
		protocol = Protocol::Unknown;
	}

	return protocol;
}

	
IPPacket::const_iterator IPPacket::ip_header_begin() {
	return ip_header;
}

IPPacket::const_iterator IPPacket::ip_header_end() {
	return ip_data;
}

IPPacket::const_iterator IPPacket::ip_data_begin() {
	return ip_data;
}

IPPacket::const_iterator IPPacket::ip_data_end() {
	return end;
}

int IPPacket::getIPHeaderLength() const {
	return ((*ip_header) & 0xf) * 4;
}

int IPPacket::getIPVersion() const {
	return (*ip_header >> 4) & 0xf;
}

string IPPacket::getSourceIP() const {
	string ip_str = "";
	uint32_t ip_int = *((uint32_t*) (ip_header + 12));
	for (int i = 0; i < 4; i++) {
		int t = (ip_int >> i * 8) & 0xff;
		ip_str += to_string(t);
		if (i + 1 != 4) {
			ip_str += ".";
		}
	}
	return ip_str;
}

string IPPacket::getDestinationIP() const {
	string ip_str = "";
	uint32_t ip_int = *((uint32_t*) (ip_header + 16));
	for (int i = 0; i < 4; i++) {
		int t = (ip_int >> i * 8) & 0xff;
		ip_str += to_string(t);
		if (i + 1 != 4) {
			ip_str += ".";
		}
	}
	return ip_str;
}
}
