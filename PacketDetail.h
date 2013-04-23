#ifndef PACKETDETAIL_H_
#define PACKETDETAIL_H_

#include <QDateTime>
#include <QByteArray>
#include <QString>
using namespace std;

struct PacketDetail {
	int caplen;
	int len;
	QDateTime timestamp;
	QByteArray data;
	QString src_ip;
	QString dst_ip;
	int src_port;
	int dst_port;
	QString transport_protocol;
	QString application_protocol;
};

#endif
