#ifndef UDP_HEADER_H
#define UDP_HEADER_H

typedef struct udp_header{
	u_short sport;         
	u_short dport;          
	u_short len;         
	u_short crc; 
}udp_header;

#endif
