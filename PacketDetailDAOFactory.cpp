#include "PacketDetailDAOFactory.h"
#include <string>
#include "MysqlPacketDetailDAO.h"
#include "errors.h"

PacketDetailDAOFactory* PacketDetailDAOFactory::getPacketDetailDAO(string dbtype) {
	if (dbtype == "mysql") {
		return new MysqlPacketDetailDAO();
	} else {
		throw UnsupportedDatabaseError(dbtype);
	}
}
