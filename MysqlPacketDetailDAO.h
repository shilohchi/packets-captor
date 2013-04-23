#ifndef MYSQLPACKETDETAILDAO_H_
#define MYSQLPACKETDETAILDAO_H_

#include "IPacketDetailDAO.h"
#include <QtSql>

class MysqlPacketDetailDAO : public IPacketDetailDAO {
private:
	QSqlDatabase db;
};

#endif
