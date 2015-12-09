
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<arpa/inet.h>
#include<sys/socket.h>
 
#define BUFLEN 512  
#define PORT 8888  
#define XINUPORT 52743
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(void)
{
    struct sockaddr_in si_me, si_other;
   int s, i, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];
   
    char sbuf[1024];
    
    //create a UDP socket

    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
    
   
    memset((char *) &si_me, 0, sizeof(si_me));
    
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
   
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(XINUPORT);
    inet_pton(AF_INET, "192.168.1.101", &(si_other.sin_addr));   

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
    
    //keep listening for data
    while(1)
    {
        printf("Waiting for data...\n");
        fflush(stdout);
        
      
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
        
       
        printf("Received packet from %s:%d \n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));

        printf("Received Data : %s\n" , buf);

	printf("Send a message to XINU :\n");
     	fgets(sbuf,1024,stdin);
    
        printf("Sending  %s to XINU \n", sbuf);
        
        
        if (sendto(s, sbuf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
		break;
        }

    }
 
    close(s);
    return 0;
}
