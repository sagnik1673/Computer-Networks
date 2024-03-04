#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

int main()
{
	int sockfd;
	int len;
	int res;
	struct sockaddr_un address;
	char mac[18];

	sockfd=socket(AF_UNIX,SOCK_STREAM,0);
	address.sun_family=AF_UNIX;
	strcpy(address.sun_path,"mysocket1");
	len=sizeof(address);

	if(connect(sockfd,(struct sockaddr *)&address,len)==-1)
	{
		perror("ERROR : failed to connect\n");
		exit(1);
	}
	
	printf("Enter MAC address:\n");
	fgets(mac,18,stdin);
	write(sockfd,mac,18);
	read(sockfd,mac,18);
	printf("Reversed MAC address from server : %s\n",mac);
	close(sockfd);
	exit(0);
}
