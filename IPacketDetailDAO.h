#ifndef IPACKETDETAILDAO_H_
#define IPACKETDETAILDAO_H_

#include "PacketDetail.h"

class PacketDetailDAO {
public:
	virtual void open() = 0;
	virtual void close() = 0;
	virtual void insert(const PacketDetail& packet) = 0;
};

#endif
