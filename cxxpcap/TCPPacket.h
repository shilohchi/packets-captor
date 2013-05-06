#ifndef TCPPACKET_H_
#define TCPPACKET_H_

#include "cxxpcap/IPPacket.h"

namespace cxxpcap {
class TCPPacket : public IPPacket {
private:
	int sourcePort;
	int destinationPort;

protected:
	std::uint8_t* tcp_header;
	std::uint8_t* tcp_data;
	
public:
	typedef const std::uint8_t* const_iterator;
	
	static bool isValid(std::uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol);

	TCPPacket(std::uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol);
	TCPPacket(int length, timeval timestamp, std::uint8_t* raw_data,
			int raw_data_length, Protocol datalink_protocol);
	TCPPacket(const TCPPacket& p);
	
	TCPPacket::const_iterator tcp_header_begin();
	TCPPacket::const_iterator tcp_header_end();
	TCPPacket::const_iterator tcp_data_begin();
	TCPPacket::const_iterator tcp_data_end();

	int getTCPHeaderLength();

	int getSourcePort();
	int getDestinationPort();
};
}

#endif
