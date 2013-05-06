#ifndef PACKETCAPTURE_H_
#define IPACKETCAPTURE_H_
#include <pcap.h>
#include "cxxpcap/utils.h"
#include <string>
#include <vector>

namespace cxxpcap {
class PacketCapture {
private:
	const static int DEFAULT_SNAPLEN = 96;

	const static int DEFAULT_TIMEOUT = 1000;
	
	static char errbuf[PCAP_ERRBUF_SIZE];
	
	struct bpf_program fcode;

	std::string device;
	
	pcap_t* capture;

	void stringToArray(const std::string& s, char*& p);

public:
	static void findAllDevices(std::vector<NetworkInterface>& list);
	
	PacketCapture();

	void setFilter(std::string filter);
	
	void open(std::string device, bool promisc, int snaplen = DEFAULT_SNAPLEN, int timeout = DEFAULT_TIMEOUT);

	void startCapturing(int count = -1);

	void stopCapturing();

	void close();
};
}

#endif
