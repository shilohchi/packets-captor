#include "cxxpcap/Packet.h"
#include <ctime>

using namespace std;

namespace cxxpcap {
Packet::Packet(const uint8_t* raw_data, int raw_data_length) :
		Packet(raw_data_length, {0, 0}, raw_data, raw_data_length) {
}

Packet::Packet(int length, timeval timestamp, const uint8_t* raw_data, int raw_data_length) {
	this->length = length;
	this->timestamp = timestamp;
	this->start = new uint8_t[raw_data_length];
	this->end = this->start + raw_data_length;
	for (int i = 0; i < raw_data_length; i++) {
		this->start[i] = raw_data[i];
	}
}

Packet::Packet(const Packet& p) {}

Packet::~Packet() {
	delete[] start;
}

int Packet::getLength() const {
	return length;
}

timeval Packet::getTimestamp() const {
	return timestamp;
}

Packet::const_iterator Packet::raw_data_begin() const {
	return this->start;
}

Packet::const_iterator Packet::raw_data_end() const {
	return this->end;
}

int Packet::raw_data_length() const {
	return end - start;
}
}
