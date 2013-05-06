#include "cxxpcap/TCPPacket.h"

namespace cxxpcap {
bool TCPPacket::isValid(uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) {
	if (!IPPacket::isValid(raw_data, raw_data_length, datalink_protocol)) {
		return false;
	}
	IPPacket pkt(raw_data, raw_data_length, datalink_protocol);
	if (pkt.raw_data_end() < pkt.ip_data_begin() + 20) {
		return false;
	}
	return true;
}

TCPPacket::TCPPacket(uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) :
		TCPPacket(raw_data_length, {0, 0}, raw_data, raw_data_length, datalink_protocol) {
}

TCPPacket::TCPPacket(int length, timeval timestamp, uint8_t* raw_data,
		int raw_data_length, Protocol datalink_protocol) :
		IPPacket(length, timestamp, raw_data, raw_data_length, datalink_protocol) {
	if (!isValid(raw_data, raw_data_length, datalink_protocol)) {
		throw PacketError("Failed to construct TCPPacket.");
	}
	this->tcp_header = this->ip_data;
	this->tcp_data = this->ip_data + getTCPHeaderLength();
}

TCPPacket::TCPPacket(const TCPPacket& p) :
		IPPacket(p) {
}

TCPPacket::const_iterator TCPPacket::tcp_header_begin() {
	return tcp_header;
}

TCPPacket::const_iterator TCPPacket::tcp_header_end() {
	return tcp_data;
}

TCPPacket::const_iterator TCPPacket::tcp_data_begin() {
	return tcp_data;
}

TCPPacket::const_iterator TCPPacket::tcp_data_end() {
	return end;
}

int TCPPacket::getSourcePort() {
	if (this->sourcePort == -1) {
		this->sourcePort = int(*tcp_header) << 8 + *(tcp_header + 1);
	}
	return this->sourcePort;
}

int TCPPacket::getDestinationPort() {
	if (this->destinationPort == -1) {
		this->destinationPort = int(*tcp_header + 2) << 8 + *(tcp_header + 3);
	}
	return this->destinationPort;
}
}
