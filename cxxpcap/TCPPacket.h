#ifndef TCPPACKET_H_
#define TCPPACKET_H_

#include "cxxpcap/IPPacket.h"

namespace cxxpcap {
class TCPPacket : public IPPacket {
protected:
	std::uint8_t* tcp_header;
	std::uint8_t* tcp_data;
	
public:
	typedef const std::uint8_t* const_iterator;
	
	static bool isValid(const std::uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol);

	TCPPacket(const std::uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol);
	TCPPacket(int length, timeval timestamp, const std::uint8_t* raw_data,
			int raw_data_length, Protocol datalink_protocol);
	TCPPacket(const TCPPacket& p);
	
	TCPPacket::const_iterator tcp_header_begin() const;
	TCPPacket::const_iterator tcp_header_end() const;
	TCPPacket::const_iterator tcp_data_begin();
	TCPPacket::const_iterator tcp_data_end();

	int getTCPHeaderLength();

	int getSourcePort() const;
	int getDestinationPort() const;
};
}

#endif
