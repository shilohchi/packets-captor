#ifndef HANDLE_PACKET_INTERFACE
#define HANDLE_PACKET_INTERFACE

//typedef void (CALLBACK* FUNC_PTR) (u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
typedef void (* FUNC_PTR)(u_char *, const struct pcap_pkthdr *,
	const u_char *);

class IHandlePacket
{
public:
	FUNC_PTR m_foo;

	//virtual FUNC_PTR handlePacket(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
	virtual FUNC_PTR get_foo();
	
};


class D: public IHandlePacket {
public:
	D() { m_foo = foo;}

	void static foo(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
	
	FUNC_PTR get_foo()
	{
		return m_foo;
	}
};

void D::foo(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{

}
#endif