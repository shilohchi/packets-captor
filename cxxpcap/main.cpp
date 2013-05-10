#include <memory>
#include "cxxpcap/cxxpcap.h"
#include <iostream>
#include <vector>

using namespace cxxpcap;
using namespace std;

int main() {
	PacketCapture capture;
	capture.open("eth0", 0, 65535);
	capture.addHandler([] (std::shared_ptr<const Packet> packet) {
	});
	capture.start(0);
}
