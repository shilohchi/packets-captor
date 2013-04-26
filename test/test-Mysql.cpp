#include "ConfigSingleton.h"
#include <map>
#include <QApplication>
#include <string>
#include <iostream>
#include "IPacketDetailDAO.h"
#include "PacketDetailDAOFactory.h"
#include <QDateTime>

using namespace std;

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	IPacketDetailDAO* dao = PacketDetailDAOFactory::getPacketDetailDAO("mysql");
	dao->open();
	PacketDetail packet;
	packet.caplen = 17;
	packet.len = 17;
	packet.src_ip = "172.20.52.137";
	packet.dst_ip = "202.202.0.33";
	packet.src_port = 3030;
	packet.dst_port = 8080;
	packet.application_protocol = "qq";
	packet.transport_protocol = "";
	packet.data = "";
	packet.timestamp = QDateTime::currentDateTime();
	dao->insert(packet);
	dao->close();
	return app.exec();
}
