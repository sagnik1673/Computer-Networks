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
	char buff[50];
	struct sockaddr_un s_address, c_address;

	int i, c=0;

	unlink("mysocket");
	s_sock_fd=socket(AF_UNIX,SOCK_STREAM,0);
	s_address.sun_family=AF_UNIX;
	strcpy(s_address.sun_path,"mysocket");
	s_len=sizeof(s_address);

	bind(s_sock_fd,(struct sockaddr *)&s_address,s_len);
	listen(s_sock_fd,5);
	while(1)
	{
		printf("Server is waiting.\n");
		c_len=sizeof(c_address);
		c_sock_fd=accept(s_sock_fd,(struct sockaddr *)&c_address,&c_len);
		printf("Connection established.\n");
		read(c_sock_fd,buff,sizeof(buff));
		printf("Data received from client: %s\n",buff);
		for(i=0;i<strlen(buff);i++)
		{
			if(buff[i]=='1')
				c++;
			if(buff[i]!='1'&&buff[i]!='0')
				break;
		}
		if(c%2==0)
			buff[i]='0';
		else
			buff[i]='1';
		printf("Data sent to the client: %s\n",buff);

		write(c_sock_fd,buff,sizeof(buff));
		close(c_sock_fd);
	}
}
