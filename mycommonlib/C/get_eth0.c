/*******************************************************************
*    > F-Name :  get_eth0.c
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Mon 14 Oct 2019 08:41:22 PM CST
*******************************************************************/


#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>


unsigned getipbyif(const char* ifname)
{
    
    if(!ifname)
    return 0;
    
    register int fd, intrface;
    struct ifreq buf[10];
    struct ifconf ifc;
    unsigned ip = 0; 
    
    if((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
    {
         ifc.ifc_len = sizeof(buf);
         ifc.ifc_buf = (caddr_t)buf;
         if(!ioctl(fd, SIOCGIFCONF, (char*)&ifc))
         {       
             intrface = ifc.ifc_len / sizeof(struct ifreq); 
             while(intrface-- > 0)  
             {       
                  if(strcmp(buf[intrface].ifr_name, ifname) == 0)
                  {       
                         if(!(ioctl(fd, SIOCGIFADDR, (char *)&buf[intrface])))
                         ip = (unsigned)((struct sockaddr_in *)(&buf[intrface].ifr_addr))->sin_addr.s_addr;
                         break;  
                   }       
            }       
         }       
      close(fd);
   }


    return ip;
}

int ip2str(char *str, uint32_t ip) 
{
         if(str == NULL)  return -1;

	unsigned char *c = (unsigned char *)&ip;
	if(c[0]>=100) {
		*str++ = '0' + c[0]/100;
		*str++ = '0' + (c[0]/10)%10;
		*str++ = '0' + c[0]%10;
	} else if(c[0]>=10) {
		*str++ = '0' + c[0]/10;
		*str++ = '0' + c[0]%10;
	} else
		*str++ = '0' + c[0];
	*str++ = '.';

	if(c[1]>=100) {
		*str++ = '0' + c[1]/100;
		*str++ = '0' + (c[1]/10)%10;
		*str++ = '0' + c[1]%10;
	} else if(c[1]>=10) {
		*str++ = '0' + c[1]/10;
		*str++ = '0' + c[1]%10;
	} else
		*str++ = '0' + c[1];
	*str++ = '.';

	if(c[2]>=100) {
		*str++ = '0' + c[2]/100;
		*str++ = '0' + (c[2]/10)%10;
		*str++ = '0' + c[2]%10;
	} else if(c[2]>=10) {
		*str++ = '0' + c[2]/10;
		*str++ = '0' + c[2]%10;
	} else
		*str++ = '0' + c[2];
	*str++ = '.';

	if(c[3]>=100) {
		*str++ = '0' + c[3]/100;
		*str++ = '0' + (c[3]/10)%10;
		*str++ = '0' + c[3]%10;
	} else if(c[3]>=10) {
		*str++ = '0' + c[3]/10;
		*str++ = '0' + c[3]%10;
	} else
		*str++ = '0' + c[3];

        return 0;
}

int main()
{ 
   char ip[30];
   unsigned eth0_ip= getipbyif("eth1");

  printf("%u\n", eth0_ip);
   
   ip2str(ip,eth0_ip); 	

  printf("%s\n", ip);
 
   return 0;
}

