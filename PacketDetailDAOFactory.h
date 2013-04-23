#ifndef PACKETDETAILDAOFACTORY_H_
#define PACKETDETAILDAOFACTORY_H_

#include "IPacketDetailDAO.h"

class PacketDetailDAOFactory {
public:
	IPacketDetailDAO* getPacketDetailDAO(string dbtype);
}
