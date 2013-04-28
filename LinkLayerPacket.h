#ifndef LINKPACKET_H
#define LINKPACKET_H
#include "pcap.h"
class LinkLayerPacket
{	
public:
	struct pcap_pkthdr header;
	u_char* data;

	LinkLayerPacket(const struct pcap_pkthdr* header,const u_char *data)
	{
		if(header==NULL||data==NULL)
		{
			return;
		}else
		{
			this->header = *header;
			this->data = new u_char[header->caplen];
			for(int i = 0;i<header->caplen;i++)
			{
				this->data[i] = data[i];
			}
		}
	}

	LinkLayerPacket(const LinkLayerPacket& linkLayerPacket)
	{
		this->header = linkLayerPacket.header;
		this->data = new u_char[linkLayerPacket.header.caplen];
		for(int i = 0;i<linkLayerPacket.header.caplen;i++)
		{
			this->data[i] = linkLayerPacket.data[i];
		}
	}


	~LinkLayerPacket()
	{
		if(data==NULL)
		{
			return;
		}
		else
		{
			delete []data;
		}
	}
	
};
#endif