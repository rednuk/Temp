#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

void parse(char *cmd,char **arguvec)
{
	while(*cmd!='\0')
	{
		while(*cmd==' '|| *cmd=='\t'|| *cmd=='\n')
		*cmd++='\0';
		*arguvec++=cmd;
		while(*cmd!='\0'&&*cmd!=' '&& *cmd!='\t' && *cmd!='\n')
		cmd++;
	}
	*arguvec='\0';
}

void cmdexecute(char **arguvec)
{
	pid_t pid;
	int status;
	pid=fork();
	if(pid<0)
	{
		printf("\nerror in creating fork");
		exit(0);
	}
	else if(pid==0)
	{
		if(execvp(*arguvec,arguvec)<0)
		{
			printf("\nerror in calling exec");
			exit(0);
		}
	}
	else
	{
		while(wait(&status)!=pid);
	}
}

int main()
{
	char cmd[1024];
	char *arguvec[20];
	while(1)
	{
		printf("[MYSHELL]");
		//gets(cmd);
		scanf("%20s",cmd);
		parse(cmd,arguvec);
		if(strcmp(arguvec[0],"exit")==0)
		{
			exit(0);
		}
		cmdexecute(arguvec);
	}
	return 0;
}