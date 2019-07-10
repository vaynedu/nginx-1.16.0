#include <stdio.h>
#include <stdint.h>


int check_ipv4_valid(const char *ip_str)
{
   uint8_t ip[4];

   sscanf(ip_str, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);

   if(ip[0] < 0 || ip[0] > 256) return -1;
   if(ip[1] < 0 || ip[1] > 256) return -1;  
   if(ip[2] < 0 || ip[2] > 256) return -1;
   if(ip[3] < 0 || ip[3] > 256) return -1;


   printf("%u \n",  ip[0] * 256 * 256 * 256 + ip[1] * 256 * 256  + ip[2]  * 256 + ip[3]);
  
   return 0;

}


int  ipv4_to_int(const char *ip_str, uint32_t *ip)
{
   
  /* check params*/
  if(ip_str == NULL || ip == NULL)
  {
     return -1;
  }

  /* the ip  valid?  */
  
  if(check_ipv4_valid(ip_str) != 0)
  {
    return -2;
  }


   uint32_t mask = 256 * 256 * 256; 
   unsigned char c = 0;
   *ip = 0; 

   /*
    * ip : 1.1.1.1
    *
    * uint32_t : 16843009
    *
    * 1 + 1*256 + 1*256*256 + 1*256*256*256
    */
    
    while(1)
    {
       if(*ip_str == '\0')
       {
           break;
       }

       if(*ip_str >= '0'  && *ip_str <= '9')
       {
           c = c * 10 + *ip_str - '0';
       }
       
       if(*ip_str == '.' || *(ip_str+1) == '\0')
       {
          *ip += c * mask;
          c = 0;
          mask /= 256; 
       }
       
       ip_str++;
    }
     
    return 0;
}


int main()
{
  int ret = -1;
   
  uint32_t ip = 0;
 
  ret = ipv4_to_int("1.1.1.1", &ip);
  printf("ret = %d, ip_int : %u\n",ret, ip);


  ret = ipv4_to_int("255.255.255.255", &ip);
  printf("ret = %d, ip_int : %u\n",ret, ip);


  ret = ipv4_to_int("123.1.1.1", &ip);
  printf("ret = %d, ip_int : %u\n",ret, ip);
  


   return 0;
}





