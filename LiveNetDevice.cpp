#include "pcap.h"
#include "LiveNetDevice.h"
#include <vector>
#include<iostream>
using std::vector;
using std::cout;
using std::endl;

LiveNetDevice* LiveNetDevice::liveNetDevice = NULL;

LiveNetDevice::LiveNetDevice()
{
	pcap_if_t *deviceList ;
	char errBuf[PCAP_ERRBUF_SIZE];


	if(pcap_findalldevs(&deviceList,errBuf)==-1)
	{   
		return ;
	}

	for(pcap_if_t *device = deviceList;device!=NULL;device = device->next)
	{
		allNetDevice.push_back(device);
	}

}

LiveNetDevice* LiveNetDevice::getInstance()
{
	if(liveNetDevice==NULL)
	{
		liveNetDevice = new LiveNetDevice();
	}
	return liveNetDevice;
}

LiveNetDevice::~LiveNetDevice()
{
	
}

void LiveNetDevice::destroy()
{
	if(liveNetDevice!=NULL)
	{
		delete liveNetDevice;
	}
}


vector<pcap_if_t*> &  LiveNetDevice::getAllNetDevice()
{
	return allNetDevice;
}

