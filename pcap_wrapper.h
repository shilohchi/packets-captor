#include <stdexcept>

using namespace std;

namespace pcap {

class PcapError: public runtime_error {
public:
	PcapError(char* msg); 
};

typedef void (*packet_handler_t)(Packet packet);

class Packet {
public:
	int caplen;
	u_char* data;
