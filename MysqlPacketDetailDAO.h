#ifndef MYSQLPACKETDETAILDAO_H_
#define MYSQLPACKETDETAILDAO_H_

#include "IPacketDetailDAO.h"
#include <QtSql>
#include "PacketDetail.h"

class MysqlPacketDetailDAO : public IPacketDetailDAO {
private:
	QSqlDatabase db;

public:
	void open();
	void close();
	void insert(const PacketDetail& packet);
};

#endif
