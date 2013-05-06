#ifndef PACKETFACTORY_H_
#define PACKETFACTORY_H_

#include <ctime>
#include <cstdint>
#include "utils.h"
#include "cxxpcap/Packet.h"

namespace cxxpcap {
class PacketFactory {
public:
	static Packet* createPacket(int length, timeval timestamp, std::uint8_t* raw_data,
			 int raw_data_length, Protocol protocol);
};
}

#endif
