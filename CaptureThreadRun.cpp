#include "pcap.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "LiveNetDevice.h"
#include "LinkLayerPacket.h"
#include "ConfigSingleton.h"
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

	if(pcap_loop(dhandle,0,packet_handler,NULL)==-1)
	{
		cout<<"an error of capturing has been occurred!";
	}
	return 0;
}


static int ccount = 1;


void packet_handler(u_char *param, const struct pcap_pkthdr* header, const u_char* data)
{
	
	
	if (ccount<5)
	{
		LinkLayerPacket linkLayerPacket(header,data);
		packetQueue.push(linkLayerPacket);

		struct tm *ltime;
		char timestr[16];
		time_t local_tv_sec;

		/* 将时间戳转换成可识别的格式 */
		local_tv_sec = header->ts.tv_sec;
		ltime=localtime(&local_tv_sec);
		strftime( timestr, sizeof timestr, "%H:%M:%S", ltime);

		printf("%s,%.6d len:%d\n", timestr, header->ts.tv_usec, header->len);

		ccount++;
	}	
	
}