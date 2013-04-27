#ifndef APPLAYERPACKET_H
#define APPLAYERPACKET_H
#include <string>
#include "pcap.h"
#include "LinkLayerPacket.h"
#include "ip_header.h"

using std::string;
class AppLayerPacket
{

public:
	string src_ip;
	string dst_ip;
	u_short src_port;
	u_short dst_port;
	string tran_layer_protocol;
	string app_layer_protocoal;
	struct timeval ts;
	int caplen;
	int len;
	u_char *data;
	AppLayerPacket(LinkLayerPacket linkLayerPacket);
	AppLayerPacket(const AppLayerPacket& appLayerPacket);
	~AppLayerPacket(){};

private:
	AppLayerPacket(){};
	void processUdpPacket(LinkLayerPacket linkLayerPacket);
	void processTcpPacket(LinkLayerPacket linkLayerPacket);
	bool isUdpPacket(LinkLayerPacket linkLayerPacket);
	bool isTcpPacket(LinkLayerPacket linkLayerPacket);
	string IntToString(u_char c);
	string IpToString(ip_address ipAddress);
	u_short ntohs(u_short port);

};  
        
#endif