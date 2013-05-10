#ifndef DATALINKINFO_H_
#define DATALINKINFO_H_

#include <cstdint>
#include "cxxpcap/utils.h"

namespace cxxpcap {
class DatalinkInfo {
public:
	virtual Protocol getProtocol() = 0;
	virtual int getLength() = 0;
};

class EthernetInfo : public DatalinkInfo {
private:
	std::uint8_t* header;

public:
	static const int LENGTH = 14;
	
	EthernetInfo(const std::uint8_t* header);
	virtual ~EthernetInfo();
	virtual Protocol getProtocol();
	virtual int getLength();
};
}
#endif

