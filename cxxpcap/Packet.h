#ifndef PACKET_H_
#define PACKET_H_

#include <cstdint>
#include <ctime>

namespace cxxpcap {
class Packet {
private:
	int length;
	timeval timestamp;
	
protected:
	std::uint8_t* start;
	std::uint8_t* end;

public:
	typedef const std::uint8_t* const_iterator;
	
	Packet(std::uint8_t* raw_data, int raw_data_length);
	Packet(int length, timeval timestamp, std::uint8_t* raw_data, int raw_data_length);
	Packet(const Packet& p);

	~Packet();

	int getLength();
	timeval getTimestamp();

	Packet::const_iterator raw_data_begin();
	Packet::const_iterator raw_data_end();

	int raw_data_length();
};
}
#endif
