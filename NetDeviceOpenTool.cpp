#include "pcap.h"
#include "NetDeviceOpenTool.h"

 pcap_t* NetDeviceOpenTool::openDevice(pcap_if_t* device,int snaplen,int flags,int read_timeout,struct pcap_rmtauth *auth, char* errbuf)
{
	return pcap_open( device->name,snaplen,flags,read_timeout, auth, errbuf);
}
