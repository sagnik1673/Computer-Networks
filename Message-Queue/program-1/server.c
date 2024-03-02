#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MAX 50

struct my_msg
{
	long int msg_type;
	char some_text[MAX];
};

int main()
{
	int msgid;
	char buffer[20];
	struct my_msg some_data;
	msgid=msgget((key_t)12345,0666|IPC_CREAT);
	msgrcv(msgid,(void *)&some_data,MAX,1,0);
	printf("Data recieved: %s\n",some_data.some_text);
	int l=strlen(some_data.some_text);
	int i,j,c=0;
	for(j=0;j<l;j++)
	{
		if(some_data.some_text[j]=='0')
		{
			strcat(buffer,"0");			
			c++;
		}
		if(some_data.some_text[j]=='1')
		{
			strcat(buffer,"1");
			c=0;
		}
		if(c==5)
		{
			strcat(buffer,"1");
			c=0;
		}
	}
	some_data.msg_type=2;
	strcpy(some_data.some_text,buffer);
	if(msgsnd(msgid,(void *)&some_data,MAX,0)==-1)
		printf("Message not sent.\n");
	msgctl(msgid,IPC_RMID,0);
}
