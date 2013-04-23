#ifdef PACKETDETAIL_H_
#define PACKETDETAIL_H_

#include <QDateTime>
#include <QByteArray>
#include <string>
using namespace std;

struct PacketDetail {
	int caplen;
	int len;
	QDateTime timestamp;
	QByteArray data;
	string src_ip;
	string dst_ip;
	int src_port;
	int dst_port;
	string transport_protocol;
	string application_protocol;
};

#endif
