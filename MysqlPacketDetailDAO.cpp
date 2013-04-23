#include "MysqlPacketDetailDAO.h"
#include "ConfigSingleton.h"
#include <map>
#include <QtSql>
#include <string>
#include "errors.h"
#include "PacketDetail.h"

using namespace std;

void MysqlPacketDetailDAO::open() {
	multimap<string, string>* config = ConfigSingleton::getConfig();	
	multimap<string, string>::iterator it;

	this->db = QSqlDatabase::addDatabase("QMYSQL");
	it = config->find("database-host");
	db.setHostName(it->second);
	it = config->find("database-user");
	db.setUserName(it->second);
	it = config->find("database-password");
	db.setPassword(it->second);
	it = config->find("database-name");

	if (!db.open()) {
		throw SqlError("Cannot open the database!");	
	}
}

void MysqlPacketDetailDAO::close() {
	this->db.close();
}

void insert(const PacketDetail& packet) {
	QString sql = "insert into packets_details ("
			"caplen, len, timestamp, data, src_ip, dst_ip, "
			"src_port, dst_port, transport_protocol, "
			"application_protocol) values (:caplen, :len "
			":timestamp, :src_port, :dst_ip, :src_port "
			":dst_port, :transport_protocol, :application_protocol)";
	QSqlQuery query;
	query.prepare(sql);
	query.bindValue(":caplen", packet.caplen);
	query.bindValue(":len", packet.len);
	query.bindValue(":timestamp", packet.timestamp);
	query.bindValue(":data", packet.data);
	query.bindValue(":src_ip", packet.src_ip);
	query.bindValue(":dst_ip", packet.dst_ip);
	query.bindValue(":src_port", packet.src_port);
	query.bindValue(":dst_port", packet.dst_port);
	query.bindValue(":transport_protocol", packet.transport_protocol);
	query.bindValue(":application_protocol", packet.application_protocol);
	query.exec();
}
