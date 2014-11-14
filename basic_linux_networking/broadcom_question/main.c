#include <stdio.h>
#include <linux/if_ether.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <linux/udp.h>

#define HARD_CODED_SIZE 78

unsigned char inpkt[HARD_CODED_SIZE] =
{0x01, 0x00, 0x5e, 0x00, 0x00, 0x02, 0x00, 0x1a,
 0x2f, 0x7c, 0x02, 0xc8, 0x08, 0x00, 0x45, 0xc0,
 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11,
 0x8e, 0x6d, 0x0a, 0x8c, 0x40, 0x02, 0xe0, 0x00,
 0x00, 0x02, 0x07, 0xc1, 0x07, 0xc1, 0x00, 0x1c,
 0xe2, 0xe1, 0x00, 0x00, 0x08, 0x03, 0x0a, 0x64,
 0x40, 0x00, 0x63, 0x69, 0x73, 0x63, 0x6f, 0x00,
 0x00, 0x00, 0x0a, 0x8c, 0x40, 0x01};

unsigned short checksum(unsigned short *buff, int len)
{
    int sum = 0;
    unsigned short answer = 0;
    unsigned short *w = buff;
    int nleft = len;

    while(nleft > 1) {
        sum += ntohs(*w++);
        nleft -= 2;
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    answer = ~sum;

    return(answer);
}

unsigned short udp_checksum(unsigned short *buff, int len, unsigned int src_addr, unsigned int dest_addr)
{
    unsigned short *buf=buff;
    unsigned short *ip_src=(void *)&src_addr, *ip_dst=(void *)&dest_addr;
    unsigned int sum;
    unsigned int length=len;

    sum = 0;
    while (len > 1) {
        sum += ntohs(*buf++);
        if (sum & 0x80000000) {
            sum = (sum & 0xFFFF) + (sum >> 16);
        }
        len -= 2;
    }

    if ( len & 1 ) {
        sum += ntohs(*((uint8_t *)buf));
    }

    sum += ntohs(*(ip_src++));
    sum += ntohs(*ip_src);

    sum += ntohs(*(ip_dst++));
    sum += ntohs(*ip_dst);

    sum += IPPROTO_UDP;
    sum += length;

    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    return ( (unsigned short)(~sum) );
}

void main(void)
{
   int i;
   uint32_t inpkt_host = ntohl(inpkt);
   for (i=0; i<HARD_CODED_SIZE; i++){
   	printf("%c", inpkt[i]);
   	//if(i%32==0)
   	//	puts(" ");
   }
   //printf("Hello\n");
}

