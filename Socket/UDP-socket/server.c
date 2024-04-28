#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	char *ip="127.0.0.1";
	int port=1234;
	
	int sfd;
	struct sockaddr_in saddr, caddr;
	char buffer[1024];
	socklen_t addr_size;
	int n;

	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd<0)
	{
		perror("[-] socket error");
		exit(1);
	}

	memset(&saddr,'\0',sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(port);
	saddr.sin_addr.s_addr=inet_addr(ip);

	n=bind(sfd,(struct sockaddr*)&saddr,sizeof(saddr));
	if(n<0)
	{
		perror("[-] bind error");
		exit(1);
	}

	bzero(buffer,1024);
	addr_size=sizeof(caddr);
	recvfrom(sfd,buffer,1024,0,(struct sockaddr*)&caddr,&addr_size);
	printf("[+] Data recieved from client: %s\n",buffer);

	bzero(buffer,1024);
	strcpy(buffer,"Welcome to the UDP Sever...");
	sendto(sfd,buffer,1024,0,(struct sockaddr*)&caddr,sizeof(caddr));
	printf("[+] Data sent to client: %s\n",buffer);
	
	return 0;
}
