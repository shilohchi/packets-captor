#include "pcap.h"
#include "ip_header.h"
#include "udp_header.h"
#include "tcp_header.h"
#include <string>
#include "LinkLayerPacket.h"
#include "AppLayerPacket.h"
using std::string;

//构造函数
// 参数说明 linkLayerPacket为链路层数据包
AppLayerPacket::AppLayerPacket(LinkLayerPacket linkLayerPacket)
{
	this->ts = linkLayerPacket.header.ts;
	this->caplen = linkLayerPacket.header.caplen;
	this->len = linkLayerPacket.header.len;
	this->data = new u_char[linkLayerPacket.header.caplen];
	for(int i = 0 ;i<linkLayerPacket.header.caplen;i++)
	{
		this->data[i] = linkLayerPacket.data[i];
	}
	if(isUdpPacket(linkLayerPacket))
	{
		processUdpPacket(linkLayerPacket);
	}else if(isTcpPacket(linkLayerPacket))
	{
		processTcpPacket(linkLayerPacket);
	}else
	{
		this->tran_layer_protocol = "invalid protocol";
	}
}


AppLayerPacket::AppLayerPacket(const AppLayerPacket& appLayerPacket)
{
	this->data = new u_char[appLayerPacket.caplen];
	for(int i = 0;i<appLayerPacket.caplen; i++)
	{
		this->data[i] = appLayerPacket.data[i];
	}
	this->caplen = appLayerPacket.caplen;
	this->len = appLayerPacket.len;
	this->ts = appLayerPacket.ts;
	this->src_ip = appLayerPacket.src_ip;
	this->src_port = appLayerPacket.src_port;
	this->dst_ip = appLayerPacket.dst_ip;
	this->dst_port = appLayerPacket.dst_port;
	this->tran_layer_protocol = appLayerPacket.tran_layer_protocol;
	this->app_layer_protocoal = appLayerPacket.app_layer_protocoal;
}

//判断链路层数据包的传输层协议是否为UDP协议，如果是返回true，否则返回false
bool  AppLayerPacket::isUdpPacket(LinkLayerPacket linkLayerPacket)
{
	bool flag = false;
	char* cp = (char*)(linkLayerPacket.data + 23);
	if(*cp==17)
	{
		flag = true;
	}
	return flag;
}

//判断链路层数据包的传输层协议是否为TCP协议，如果是返回true，否则返回false
bool AppLayerPacket::isTcpPacket(LinkLayerPacket linkLayerPacket)
{
	bool flag = false;
	char* cp = (char*)(linkLayerPacket.data + 23);
	if(*cp==6)
	{
		flag = true;
	}
	return flag;
}

//将链路层帧解析成所需的应用层UDP数据包，所传入包传输层必须是UDP协议
void AppLayerPacket::processUdpPacket(LinkLayerPacket linkLayerPacket)
{
	this->tran_layer_protocol = "udp";
	ip_header* ipHeader = (ip_header*)(linkLayerPacket.data+14);

	int ipLength = (ipHeader->ver_ihl&0x0f)*4;
	
	udp_header* udpHeader = (udp_header*)((char*)ipHeader+ipLength);

	this->src_port = ntohs(udpHeader->sport);
	this->dst_port = ntohs(udpHeader->dport);
	this->src_ip = IpToString(ipHeader->saddr);
	this->dst_ip = IpToString(ipHeader->daddr);
	this->app_layer_protocoal = "unknown";

}

//将链路层帧解析成所需的应用层TCP数据包，所传入包传输层必须是TCP协议
void AppLayerPacket::processTcpPacket(LinkLayerPacket linkLayerPacket)
{

	this->tran_layer_protocol = "tcp";
	ip_header* ipHeader = (ip_header*)(linkLayerPacket.data+14);

	int ipLength = (ipHeader->ver_ihl&0x0f)*4;

	tcp_header* tcpHeader = (tcp_header*)((char*)ipHeader+ipLength);
	this->src_ip = IpToString(ipHeader->saddr);
	this->dst_ip = IpToString(ipHeader->daddr);
	this->src_port = ntohs(tcpHeader->sport);
	this->dst_port = ntohs(tcpHeader->dport);
	this->app_layer_protocoal = "unknown";

}

//convert struct ip_address object to a string which is intuitionistic to people
string AppLayerPacket::IpToString(ip_address ipAddress)
{
	string firstByte = IntToString(ipAddress.byte1);
	string secondByte = IntToString(ipAddress.byte2);
	string thirdByte = IntToString(ipAddress.byte3);
	string fourthByte = IntToString(ipAddress.byte4);
	string strSpot = ".";
	string ipStr = firstByte+strSpot+secondByte+strSpot+thirdByte+strSpot+fourthByte;
	return ipStr;
}
// convert unsigned char to integer ,then convert to string.
string AppLayerPacket::IntToString(u_char c)
{
		char arr[4];
		int i = 0;
		int flag = false;

		if(c/100!=0)
		{
			arr[i]=c/100+48;
			i++;
			c = c%100;
			flag = true;
		}
		if((c/10!=0)||(flag==true))
		{
			arr[i]=c/10+48;
			i++;
			c = c%10;
			flag = true;
		}
		arr[i] = c+48;
		i++;
		arr[i] = '\0';

		string str(arr);
		return str;
}


