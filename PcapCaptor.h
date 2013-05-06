class PcapCaptor {
public:
	static vector<string> getDeviceList();
	static openDevice(string interface, int snaplen, bool promisc,, int to_ms);
	void setFilter(string condition);

