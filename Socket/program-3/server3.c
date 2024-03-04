#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

int main()
{
	int s_sock_fd, c_sock_fd, s_len, c_len;
	char mac[18], revmac[18];
	struct sockaddr_un s_address, c_address;

	int i;

	unlink("mysocket1");
	s_sock_fd=socket(AF_UNIX,SOCK_STREAM,0);
	s_address.sun_family=AF_UNIX;
	strcpy(s_address.sun_path,"mysocket1");
	s_len=sizeof(s_address);

	bind(s_sock_fd,(struct sockaddr *)&s_address,s_len);
	listen(s_sock_fd,5);
	
	printf("Server is waiting.\n");
	c_len=sizeof(c_address);
	c_sock_fd=accept(s_sock_fd,(struct sockaddr *)&c_address,&c_len);
	printf("Connection established.\n");
	
	read(c_sock_fd,mac,18);
	printf("Data received from client: %s\n",mac);
	for(i=17;i>=1;i--)
		revmac[i-1]=mac[17-i];
	revmac[17]='\0';
	
	printf("Data sent to the client: %s\n",revmac);
	write(c_sock_fd,revmac,18);
	close(c_sock_fd);
}
