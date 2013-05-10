#ifndef PACKETFACTORY_H_
#define PACKETFACTORY_H_

#include <ctime>
#include <cstdint>
#include "utils.h"
#include "cxxpcap/Packet.h"
#include <memory>

namespace cxxpcap {
class PacketFactory {
public:
	static std::shared_ptr<const Packet> createPacket(int length, timeval timestamp, 
			const std::uint8_t* raw_data, int raw_data_length, Protocol protocol);
};
}

#endif
