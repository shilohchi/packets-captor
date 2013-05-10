#include "cxxpcap/UDPPacket.h"
#include <glog/logging.h>

namespace cxxpcap {
bool UDPPacket::isValid(const uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) {
	if (!IPPacket::isValid(raw_data, raw_data_length, datalink_protocol)) {
		return false;
	}
	IPPacket pkt(raw_data, raw_data_length, datalink_protocol);
	if (pkt.getIPProtocol() != Protocol::UDP || pkt.raw_data_end() < pkt.ip_data_begin() + 8) {
		return false;
	}
	return true;
}

UDPPacket::UDPPacket(const uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) :
		UDPPacket(raw_data_length, {0, }, raw_data, raw_data_length, datalink_protocol) {
}

UDPPacket::UDPPacket(int length, timeval timestamp, const uint8_t* raw_data,
		int raw_data_length, Protocol datalink_protocol) :
		IPPacket(length, timestamp, raw_data, raw_data_length, datalink_protocol) {
	this->udp_header = this->ip_data;
	this->udp_data = this->ip_data + getUDPHeaderLength();
}

UDPPacket::UDPPacket(const UDPPacket& p) :
		IPPacket(p) {
}

UDPPacket::const_iterator UDPPacket::udp_header_begin() {
	return udp_header;
}

UDPPacket::const_iterator UDPPacket::udp_header_end() {
	return udp_data;
}

UDPPacket::const_iterator UDPPacket::udp_data_begin() {
	return udp_data;
}

UDPPacket::const_iterator UDPPacket::udp_data_end() {
	return end;
}

int UDPPacket::getUDPHeaderLength() {
	return 8;
}

int UDPPacket::getSourcePort() const {
	return (int(*udp_header) << 8) + *(udp_header + 1);
}

int UDPPacket::getDestinationPort() const {
	return (int(*udp_header + 2) << 8) + *(udp_header + 3);
}
}
