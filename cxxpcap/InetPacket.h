#ifndef INETPACKET_H_
#define INETPACKET_H_

#include "cxxpcap/Packet.h"
#include "cxxpcap/utils.h"
#include "cxxpcap/DatalinkInfo.h"

namespace cxxpcap {
class InetPacket : public Packet {
private:
	DatalinkInfo* datalinkInfo;

protected:
	std::uint8_t* datalink_header;
	std::uint8_t* datalink_data;

public:
	typedef const std::uint8_t* const_iterator;

	static bool isValid(std::uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol);

	InetPacket(std::uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol);
	InetPacket(int length, timeval timestamp, std::uint8_t* raw_data,
			int raw_data_length, Protocol datalink_protocol);
	InetPacket(const InetPacket& p);

	DatalinkInfo* getDatalinkInfo();

	Protocol getDatalinkProtocol();

	InetPacket::const_iterator datalink_header_begin();
	InetPacket::const_iterator datalink_header_end();

	InetPacket::const_iterator datalink_data_begin();
	InetPacket::const_iterator datalink_data_end();
};
}

#endif
