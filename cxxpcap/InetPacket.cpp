#include "cxxpcap/InetPacket.h"
#include "cxxpcap/utils.h"
#include <cstdint>

using namespace std;

namespace cxxpcap {
bool InetPacket::isValid(const uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) {
	Packet pkt(raw_data, raw_data_length);
	if (datalink_protocol == Protocol::Ethernet &&
			pkt.raw_data_end() >= pkt.raw_data_begin() + 14) {
		return true;
	}
	return false;
}

InetPacket::InetPacket(const uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) :
		InetPacket(raw_data_length, {0, 0}, raw_data, raw_data_length, datalink_protocol) {
}

InetPacket::InetPacket(int length, timeval timestamp, const uint8_t* raw_data, 
		int raw_data_length, Protocol datalink_protocol) :
		Packet(length, timestamp, raw_data, raw_data_length) {
	this->datalinkInfo = shared_ptr<DatalinkInfo>(new EthernetInfo(raw_data));
	this->datalink_header = this->start;
	this->datalink_data = this->start + this->datalinkInfo->getLength();
}

InetPacket::InetPacket(const InetPacket& p) :
		Packet(p) {
}

shared_ptr<DatalinkInfo> InetPacket::getDatalinkInfo() const {
	return datalinkInfo;
}

Protocol InetPacket::getDatalinkProtocol() const {
	return datalinkInfo->getProtocol();
}

InetPacket::const_iterator InetPacket::datalink_header_begin() const {
	return datalink_header;
}

InetPacket::const_iterator InetPacket::datalink_header_end() const {
	return datalink_data;
}

InetPacket::const_iterator InetPacket::datalink_data_begin() const {
	return datalink_data;
}

InetPacket::const_iterator InetPacket::datalink_data_end() const {
	return end;
}

}
