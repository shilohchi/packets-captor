#include "cxxpcap/PacketFactory.h"
#include "cxxpcap/Packet.h"
#include "cxxpcap/InetPacket.h"
#include "cxxpcap/IPPacket.h"
#include "cxxpcap/UDPPacket.h"
#include "cxxpcap/TCPPacket.h"
#include "cxxpcap/utils.h"
#include <cstdint>
#include <ctime>

namespace cxxpcap {
Packet* PacketFactory::createPacket(int length, timeval timestamp, 
		uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol) {
	Protocol protocol = Protocol::Unknown;

	if (InetPacket::isValid(raw_data, raw_data_length, datalink_protocol)) {
		protocol = Protocol::INET;
		if (IPPacket::isValid(raw_data, raw_data_length, datalink_protocol)) {
			protocol = Protocol::IP;
			if (UDPPacket::isValid(raw_data, raw_data_length, datalink_protocol)) {
				protocol = Protocol::UDP;
			} else if (TCPPacket::isValid(raw_data, raw_data_length, datalink_protocol)) {
				protocol = Protocol::TCP;
			}
		}
	}
	
	Packet* packet;
	switch (protocol) {
	case Protocol::Unknown:
		packet = new Packet(length, timestamp, raw_data, raw_data_length);
		break;
	case Protocol::INET:
		packet = new InetPacket(length, timestamp, raw_data, raw_data_length, datalink_protocol);
		break;
	case Protocol::IP:
		packet = new IPPacket(length, timestamp, raw_data, raw_data_length, datalink_protocol);	
		break;
	case Protocol::UDP:
		packet = new UDPPacket(length, timestamp, raw_data, raw_data_length, datalink_protocol);	
		break;
	case Protocol::TCP:
		packet = new TCPPacket(length, timestamp, raw_data, raw_data_length, datalink_protocol);	
		break;
	}

	return packet;
}
}
