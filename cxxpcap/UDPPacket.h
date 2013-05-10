#ifndef UDPPACKET_H_
#define UDPPACKET_H_

#include "cxxpcap/IPPacket.h"
#include "cxxpcap/utils.h"

namespace cxxpcap {
class UDPPacket : public IPPacket {
private:
	int sourcePort;
	int destinationPort;

protected:
	std::uint8_t* udp_header;
	std::uint8_t* udp_data;

public:
	typedef std::uint8_t* const_iterator;

	static bool isValid(const std::uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol);

	UDPPacket(const std::uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol);
	UDPPacket(int length, timeval timestamp, const std::uint8_t* raw_data, int raw_data_length,
			Protocol datalink_protocol);
	UDPPacket(const UDPPacket& p);

	UDPPacket::const_iterator udp_header_begin();
	UDPPacket::const_iterator udp_header_end();
	UDPPacket::const_iterator udp_data_begin();
	UDPPacket::const_iterator udp_data_end();
	
	Protocol getUDPProtocol();
	int getUDPHeaderLength();
	
	int getSourcePort() const;
	int getDestinationPort() const;
};
}

#endif
