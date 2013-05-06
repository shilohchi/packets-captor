#include "cxxpcap/PacketCapture.h"
#include <pcap.h>
#include <vector>
#include <string>
#include "cxxpcap/utils.h"

using namespace std;

namespace cxxpcap {
PacketCapture::PacketCapture() {
	capture = NULL;
}

void stringToArray(const string& s, char*& p) {
	p = new char[s.length() + 1];
	char* q = p;
	for (char c : s) {
		*(q++) = c;
	}
	*q = '\0';
}

void PacketCapture::findAllDevices(vector<NetworkInterface>& list) {
	list.clear();
	pcap_if_t* alldevs;
	if (pcap_findalldevs(&alldevs, errbuf) == -1) {
		throw PcapError(errbuf);
	}
	for(pcap_if_t* d = alldevs; d != NULL; d = d->next) {
		NetworkInterface interface = {
			d->name,
			d->description,
		};
		list.push_back(interface);
	}
	pcap_freealldevs(alldevs);
}

void PacketCapture::setFilter(string filter) {
	bpf_u_int32 net, mask;

	char* dev;
	stringToArray(this->device, dev);
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
		throw PcapError(errbuf);
	}
	delete[] dev;	
	
	char* rule;
	stringToArray(filter, rule);
	if (pcap_compile(this->capture, &this->fcode, rule, 1, mask) == -1) {
		throw PcapError(errbuf);
	}
	delete[] rule;

	if (pcap_setfilter(this->capture, &this->fcode) == -1) {
		throw PcapError(errbuf);
	}
}

void PacketCapture::open(string device, bool promiscuous, int snaplen, int timeout) {
	char* dev;
	stringToArray(device, dev);
	if ((this->capture = pcap_open_live(dev, snaplen, promiscuous, timeout, NULL)) == NULL) {
		throw PcapError(errbuf);
	}
	this->device = device;
	delete[] dev;
}

void PacketCapture::close() {
	pcap_close(this->capture);
	this->capture = NULL;
}

void PacketCapture::startCapturing(int count) {
	pcap_loop	
}
