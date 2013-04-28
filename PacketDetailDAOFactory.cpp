#include "PacketDetailDAOFactory.h"
#include <string>
#include "MysqlPacketDetailDAO.h"
#include "errors.h"
#include "IPacketDetailDAO.h"

IPacketDetailDAO* PacketDetailDAOFactory::getPacketDetailDAO(string dbtype) {
	if (dbtype == "mysql") {
		return new MysqlPacketDetailDAO();
	} else {
		throw UnsupportedDatabaseError("");
	}
}
