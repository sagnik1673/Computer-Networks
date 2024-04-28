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
	struct sockaddr_in addr;
	char buffer[1024];
	socklen_t addr_size;

	sfd=socket(AF_INET,SOCK_DGRAM,0);
	memset(&addr,'\0',sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(ip);

	bzero(buffer,1024);
	strcpy(buffer,"Hola World!");
	sendto(sfd,buffer,1024,0,(struct sockaddr*)&addr,sizeof(addr));
	printf("[+] Data send to server: %s\n",buffer);

	bzero(buffer,1024);
	addr_size=sizeof(addr);
	recvfrom(sfd,buffer,1024,0,(struct sockaddr*)&addr,&addr_size);
	printf("[+] Data recieved from server: %s\n",buffer);

	return 0;
}
