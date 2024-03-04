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
	char buffer[17];
	struct my_msg some_data;
	msgid=msgget((key_t)12345,0666|IPC_CREAT);
	if(msgid==-1)
		printf("Message queue not created.\n");
	printf("Enter a bit-stream of 2 bytes:\n");
	fgets(buffer,17,stdin);
	some_data.msg_type=1;
	strcpy(some_data.some_text,buffer);
	if(msgsnd(msgid,(void *)&some_data,MAX,0)==-1)
		printf("Bit-stream not sent. Size has exceeded 2 bytes.\n");
	msgrcv(msgid,(void *)&some_data,MAX,2,0);
	printf("Modified bit-stream recieved from server: %s\n",some_data.some_text);
	msgctl(msgid,IPC_RMID,0);
}
