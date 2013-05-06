#include "cxxpcap/UDPPacket.h"

namespace cxxpcap {
bool UDPPacket::isValid(uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) {
	if (!IPPacket::isValid(raw_data, raw_data_length, datalink_protocol)) {
		return false;
	}
	IPPacket pkt(raw_data, raw_data_length, datalink_protocol);
	if (pkt.raw_data_end() < pkt.ip_data_begin() + 8) {
		return false;
	}
	return true;
}

UDPPacket::UDPPacket(uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) :
		UDPPacket(raw_data_length, {0, }, raw_data, raw_data_length, datalink_protocol) {
}

UDPPacket::UDPPacket(int length, timeval timestamp, uint8_t* raw_data,
		int raw_data_length, Protocol datalink_protocol) :
		IPPacket(length, timestamp, raw_data, raw_data_length, datalink_protocol) {
	if (!isValid(raw_data, raw_data_length, datalink_protocol)) {
		throw PacketError("Failed to construct UDPPacket.");
	}
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

int UDPPacket::getSourcePort() {
	if (this->sourcePort == -1) {
		this->sourcePort = int(*udp_header) << 8 + *(udp_header + 1);
	}
	return this->sourcePort;
}

int UDPPacket::getDestinationPort() {
	if (this->destinationPort == -1) {
		this->destinationPort = int(*udp_header + 2) << 8 + *(udp_header + 3);
	}
	return this->destinationPort;
}
}
