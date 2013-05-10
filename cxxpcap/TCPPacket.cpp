#include "cxxpcap/TCPPacket.h"

namespace cxxpcap {
bool TCPPacket::isValid(const uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) {
	if (!IPPacket::isValid(raw_data, raw_data_length, datalink_protocol)) {
		return false;
	}
	IPPacket pkt(raw_data, raw_data_length, datalink_protocol);
	if (pkt.getIPProtocol() != Protocol::TCP || pkt.raw_data_end() < pkt.ip_data_begin() + 20) {
		return false;
	}
	return true;
}

TCPPacket::TCPPacket(const uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) :
		TCPPacket(raw_data_length, {0, 0}, raw_data, raw_data_length, datalink_protocol) {
}

TCPPacket::TCPPacket(int length, timeval timestamp, const uint8_t* raw_data,
		int raw_data_length, Protocol datalink_protocol) :
		IPPacket(length, timestamp, raw_data, raw_data_length, datalink_protocol) {
	this->tcp_header = this->ip_data;
	this->tcp_data = this->ip_data + getTCPHeaderLength();
}

TCPPacket::TCPPacket(const TCPPacket& p) :
		IPPacket(p) {
}

TCPPacket::const_iterator TCPPacket::tcp_header_begin() const {
	return tcp_header;
}

TCPPacket::const_iterator TCPPacket::tcp_header_end() const {
	return tcp_data;
}

TCPPacket::const_iterator TCPPacket::tcp_data_begin() {
	return tcp_data;
}

TCPPacket::const_iterator TCPPacket::tcp_data_end() {
	return end;
}

int TCPPacket::getSourcePort() const {
	return (int(*tcp_header) << 8) + *(tcp_header + 1);
}

int TCPPacket::getDestinationPort() const {
	return (int(*tcp_header + 2) << 8) + *(tcp_header + 3);
}

int TCPPacket::getTCPHeaderLength() {
	return 20;
}
}
