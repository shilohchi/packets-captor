#include "cxxpcap/InetPacket.h"
#include "cxxpcap/utils.h"
#include <cstdint>

using namespace std;

namespace cxxpcap {
bool InetPacket::isValid(uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) {
	Packet pkt(raw_data, raw_data_length);
	if (datalink_protocol == Protocol::Ethernet &&
			pkt.raw_data_end() < pkt.raw_data_begin() + 14) {
		return true;
	}
	return false;
}

InetPacket::InetPacket(uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) :
		InetPacket(raw_data_length, {0, 0}, raw_data, raw_data_length, datalink_protocol) {
}

InetPacket::InetPacket(int length, timeval timestamp, uint8_t* raw_data, 
		int raw_data_length, Protocol datalink_protocol) :
		Packet(length, timestamp, raw_data, raw_data_length) {
	if (!InetPacket::isValid(raw_data, raw_data_length, datalink_protocol)) {
		throw PacketError("Failed to construct InetPacket.");
	}
	this->datalinkInfo = new EthernetInfo(raw_data);
	this->datalink_header = this->start;
	this->datalink_data = this->start + this->datalinkInfo.getLength();
}

InetPacket::InetPacket(const InetPacket& p) :
		Packet(p) {
}

DatalinkInfo* InetPacket::getDatalinkInfo() {
	return datalinkInfo;
}

Protocol InetPacket::getDatalinkProtocol() {
	return datalinkInfo->getProtocol();
}

InetPacket::const_iterator InetPacket::datalink_header_begin() {
	return datalink_header;
}

InetPacket::const_iterator InetPacket::datalink_header_end() {
	return datalink_data;
}

InetPacket::const_iterator InetPacket::datalink_data_begin() {
	return datalink_data;
}

InetPacket::const_iterator InetPacket::datalink_data_end() {
	return end;
}

}
