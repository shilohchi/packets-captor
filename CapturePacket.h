#ifndef CAPTURE_PACKET_H
#define CAPTURE_PACKET_H
class CapturePacket
{
public:

	static void loopCapture(pcap_t *p,int cnt,IHandlePacket* ,u_char * user);

};
#endif