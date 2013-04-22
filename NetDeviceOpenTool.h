#ifndef NET_DEVICE_OPEN_TOOL_H
#define NET_DEVICE_OPEN_TOOL_H
class NetDeviceOpenTool
{
public:
	static pcap_t* openDevice(pcap_if_t* device,int snaplen,int flags,int read_timeout,struct pcap_rmtauth *auth, char* errbuf);
};
#endif 