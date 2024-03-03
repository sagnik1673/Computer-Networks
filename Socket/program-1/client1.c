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
	char ip[30];

	sockfd=socket(AF_UNIX,SOCK_STREAM,0);
	address.sun_family=AF_UNIX;
	strcpy(address.sun_path,"server_socket_1");
	len=sizeof(address);

	if(connect(sockfd,(struct sockaddr *)&address,len)==-1)
	{
		perror("ERROR : failed to connect\n");
		exit(1);
	}
	
	printf("Enter IP address:\n");
	fgets(ip,30,stdin);
	write(sockfd,ip,sizeof(ip));
	read(sockfd,&res,4);
	printf("from server : %d\n",res);
	close(sockfd);
	exit(0);
}
