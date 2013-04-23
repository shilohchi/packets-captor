#ifndef PACKETDETAILDAOFACTORY_H_
#define PACKETDETAILDAOFACTORY_H_

#include "IPacketDetailDAO.h"
#include "MysqlPacketDetailDAO.h"

class PacketDetailDAOFactory {
public:
	static IPacketDetailDAO* getPacketDetailDAO(string dbtype);
};

#endif
