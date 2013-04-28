#ifndef LIVENETDEVICE_H
#define LIVENETDEVICE_H
#include <vector>
class LiveNetDevice
{
private:
	std::vector<pcap_if_t*> allNetDevice;
	static LiveNetDevice* liveNetDevice;
	LiveNetDevice();
	~LiveNetDevice();
public: 
	
	std::vector<pcap_if_t*>& getAllNetDevice();
	static LiveNetDevice* getInstance();
	static void destroy();
};
#endif