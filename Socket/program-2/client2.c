#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

int main()
{
	int sock_fd, len;
	char bs[50];
	struct sockaddr_un address;

	sock_fd=socket(AF_UNIX,SOCK_STREAM,0);
	address.sun_family=AF_UNIX;
	strcpy(address.sun_path,"mysocket");
	len=sizeof(address);

	if(connect(sock_fd,(struct sockaddr *)&address,len)==-1)
	{
		perror("Error in conecting\n");
		exit(1);
	}
	
	printf("Enter bit-stream:\n");
	fgets(bs,50,stdin);
	write(sock_fd,bs,sizeof(bs));
	read(sock_fd,bs,sizeof(bs));
	printf("Bit-stream with even parity: %s\n",bs);
	close(sock_fd);
	exit(0);
}
