#include "pcap.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "LiveNetDevice.h"
#include "LinkLayerPacket.h"
#include "ConfigSingleton.h"
#include "AppLayerPacket.h"
#include <map>


using std::endl;
using std::cout;
using std::string;

std::queue<LinkLayerPacket> packetQueue;
void packet_handler(u_char *param, const struct pcap_pkthdr* header, const u_char* data);

int main()
{
	pcap_if_t* device = NULL;
	pcap_t *dhandle = NULL;
	char errbuf[PCAP_ERRBUF_SIZE];
	//const char* filterStr = "(ip and tcp) or (ip and udp)";
	
	char* filterCp;

	u_int netmask;
	struct bpf_program fcode;

	multimap<string,string>* config = ConfigSingleton::getConfig();
	multimap<string,string>::iterator iter = config->find("network-interface");
	string interfaceName = iter->second;

	char* deviceName = new char[interfaceName.size()+1];

	int i = 0;
	for( i = 0 ;i<interfaceName.size();i++)
	{
		deviceName[i] = interfaceName[i];
	}
	deviceName[i] = '\0';

	
	string filterStrs = "";

	for(iter = config->lower_bound("low-level-filter");iter!=config->upper_bound("low-level-filter");iter++)
	{
		string temp = iter->second;
		
		filterStrs += temp;
	}
	
	filterCp = new char[filterStrs.size()+1];
	i = 0;
	for( i = 0 ;i<filterStrs.size();i++)
	{
		filterCp[i] = filterStrs[i];
	}
	filterCp[i] = '\0';

	
	
	LiveNetDevice* liveNetDevice = LiveNetDevice::getInstance();
	std::vector<pcap_if_t*> devices = liveNetDevice->getAllNetDevice();

	for(int i =0;i<devices.size();i++)
	{
		if(strcmp(devices[i]->name,deviceName)==0)
		{
			device = devices[i];
			break;
		}
	}

	if(device==NULL)
	{
		cout<<"can not find appropriate device!";
		return 0;
	}

	if((dhandle=pcap_open(device->name,10000,PCAP_OPENFLAG_PROMISCUOUS,1000,NULL,errbuf))==NULL)
	{
		cout<<"this adapter is not supported by winpcap!"<<endl;
		pcap_freealldevs(device);
		return -1;
	}

	if(pcap_datalink(dhandle)!=DLT_EN10MB)
	{
		cout<<"this app only works in ethernet network\n!"<<endl;
		return 0;
	}

	if(device->addresses != NULL)
		/* 获得接口第一个地址的掩码 */
		netmask=((struct sockaddr_in *)(device->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		/* 如果接口没有地址，那么我们假设一个C类的掩码 */
		netmask=0xffffff; 


	//编译过滤器
	if (pcap_compile(dhandle, &fcode, filterCp, 1, netmask) <0 )
	{
		fprintf(stderr,"\nUnable to compile the packet filter. Check the syntax.\n");
		/* 释放设备列表 */
		return -1;
	}

	//设置过滤器
	if (pcap_setfilter(dhandle, &fcode)<0)
	{
		fprintf(stderr,"\nError setting the filter.\n");
		/* 释放设备列表 */
		return -1;
	}


	if(pcap_loop(dhandle,0,packet_handler,NULL)==-1)
	{
		cout<<"an error of capturing has been occurred!";
	}
	return 0;
}


static int ccount = 1;


void packet_handler(u_char *param, const struct pcap_pkthdr* header, const u_char* data)
{
	
	LinkLayerPacket link(header,data);
	AppLayerPacket app(link);

	cout<<app.src_ip<<":"<<app.src_port<<"------>"<<app.dst_ip<<":"<<app.dst_port<<endl;
	
}