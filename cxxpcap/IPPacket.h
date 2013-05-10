#ifndef IPPACKET_H_
#define IPPACKET_H_

#include "cxxpcap/InetPacket.h"
#include <string>
#include "cxxpcap/utils.h"

namespace cxxpcap {
class IPPacket : public InetPacket {
private:
	std::string sourceIP;
	std::string destinationIP;

protected:
	std::uint8_t* ip_header;
	std::uint8_t* ip_data;

public:
	typedef const uint8_t* const_iterator;
	
	static bool isValid(const std::uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol);

	IPPacket(const std::uint8_t* raw_data, int raw_data_length, Protocol datalink_protocol);
	IPPacket(int length, timeval timestamp, const std::uint8_t* raw_data,
			int raw_data_length, Protocol datalink_protocol);
	IPPacket(const IPPacket& p);

	IPPacket::const_iterator ip_header_begin();
	IPPacket::const_iterator ip_header_end();
	IPPacket::const_iterator ip_data_begin();
	IPPacket::const_iterator ip_data_end();

	Protocol getIPProtocol() const;
	int getIPHeaderLength() const;

	std::string getSourceIP() const;
	std::string getDestinationIP() const;

	int getIPVersion() const;
};
}
#endif
