#include <iostream>
#include <pcap.h>

using namespace std;

void handler(u_char* param, const struct pcap_pkthdr* header, const u_char* data) {
	cout << endl;
	cout << "caplen: " << header->caplen << endl;
	cout << "len: " << header->len << endl;
	int max = header->caplen > header->len ? header->caplen : header->len;
	for (int i = 0; i < max; i++) {
		printf("%x", data[i]);
	}
	cout << endl;
	cout << data << endl;
}

int main() {
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* captor = pcap_open_live("eth0", 10, 1, 1000, errbuf);
	pcap_loop(captor, 0, handler, NULL);
}
