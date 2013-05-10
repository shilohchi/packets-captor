#ifndef INETPACKET_H_
#define INETPACKET_H_

#include "cxxpcap/Packet.h"
#include "cxxpcap/utils.h"
#include "cxxpcap/DatalinkInfo.h"
#include <memory>

namespace cxxpcap {
class InetPacket : public Packet {
private:
	std::shared_ptr<DatalinkInfo> datalinkInfo;

protected:
	std::uint8_t* datalink_header;
	std::uint8_t* datalink_data;

public:
	typedef const std::uint8_t* const_iterator;

	static bool isValid(const std::uint8_t* raw_data, const int raw_data_length, Protocol datalink_protocol);

	InetPacket(const std::uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol);
	InetPacket(int length, timeval timestamp, const std::uint8_t* raw_data,
			int raw_data_length, Protocol datalink_protocol);
	InetPacket(const InetPacket& p);

	std::shared_ptr<DatalinkInfo> getDatalinkInfo() const;

	Protocol getDatalinkProtocol() const;

	InetPacket::const_iterator datalink_header_begin() const;
	InetPacket::const_iterator datalink_header_end() const;

	InetPacket::const_iterator datalink_data_begin() const;
	InetPacket::const_iterator datalink_data_end() const;
};
}

#endif
