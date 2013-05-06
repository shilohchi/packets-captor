#include "cxxpcap/Packet.h"
#include <ctime>

using namespace std;

namespace cxxpcap {
Packet::Packet(uint8_t* raw_data, int raw_data_length) :
		Packet(raw_data_length, {0, 0}, raw_data, raw_data_length) {
}

Packet::Packet(int length, timeval timestamp, uint8_t* raw_data, int raw_data_length) {
	this->length = length;
	this->timestamp = timestamp;
	this->start = new uint8_t[raw_data_length];
	this->end = this->start + raw_data_length;
}

Packet::Packet(const Packet& p) {}

Packet::~Packet() {
	delete[] start;
}

int Packet::getLength() {
	return length;
}

timeval Packet::getTimestamp() {
	return timestamp;
}

Packet::const_iterator Packet::raw_data_begin() {
	return this->start;
}

Packet::const_iterator Packet::raw_data_end() {
	return this->end;
}

int Packet::raw_data_length() {
	return end - start;
}
}
