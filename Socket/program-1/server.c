#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

int isvalid(char *ip)
{
	int n,dot=0;
	char *tkn;
	
	//if(strcmp(ip,"0.0.0.0")==0)
	//	return 0;
	// It is valid in as much as it contains four octets, each within the range 0 through 255 inclusive.
	// However, it is not usable as a real IP address.
			
	if(ip==NULL)
		return 0;
	tkn=strtok(ip,".");
	if(tkn==NULL)
        	return 0;
	while(tkn)
	{
		if(!isdigit(*tkn))
			return 0;
		n=atoi(tkn);
		if(n>=0&&n<=255)
		{
			tkn=strtok(NULL,".");
			if(tkn!=NULL)
				dot++;
		}
		else
			return 0;
	}
	if(dot!=3)
		return 0;
	else
		return 1;
}

int main()
{
	int server_sockfd;
	int client_sockfd;
	int server_len;
	int client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;

	unlink("server_socket_1");
	server_sockfd=socket(AF_UNIX,SOCK_STREAM,0);
	
	server_address.sun_family=AF_UNIX;
	strcpy(server_address.sun_path,"server_socket_1");
	server_len=sizeof(server_address);
	bind(server_sockfd,(struct sockaddr *)&server_address,server_len);

	listen(server_sockfd,5);
	while(1)
	{
		char buff[30];
		int validity;
		printf("server waiting...\n");

		client_len=sizeof(client_address);
		client_sockfd=accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
		printf("connection established\n");

		read(client_sockfd,buff,sizeof(buff));
		printf("data read from client : %s\n",buff);
		validity=isvalid(buff);
		write(client_sockfd,&validity,sizeof(validity));
		close(client_sockfd);
	}
}
