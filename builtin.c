#include "header.h"

// execute the internal commands

void execute_cd(char **comm)
{
	int flag=0;
	char h[2]={'~', '\0'};
	if(comm[1]!=NULL)
	{
		if(strcmp(comm[1],h)!=0)
		{
			if(chdir(comm[1])!=0)
				perror("myshell:");
		}
		else
			flag=1;		
	}
	else 
	{
		if(chdir(home)!=0)
			perror("myshell:");
	}
}

void execute_echoo(char **comm)
{
	int i,start,end,j,l;
	for(i=1;i<pos;i++)
	{
		l=strlen(comm[i]);
		if(comm[i][0]=='\"' && comm[i][l-1]=='\"' && l!=1)
		{
			start=1;
			end=l-2;
		}
		else
		{
			start=0;
			end=l-1;
		}
		for(j=start;j<=end;j++)
		{
			printf("%c",comm[i][j]);
		}		
		printf(" ");
	}
	printf("\n");
}


void execute_internal(int fl)
{
	int job_no;
	if(strcmp(args[0],cd)==0)
	{
		execute_cd(args);
		if(fl==1)
			chdir(home);
	}
	//if the command is exit
	else if(strcmp(args[0],exitt)==0)
		exit(0);
	//if the command is echo
	else if(strcmp(args[0],echoo)==0)
	{
		if(args[1]!=NULL)
			execute_echoo(args);
	}
	//ifthe command is pwd
	else if(strcmp(args[0],pwdd)==0)
	{
		if(getcwd(pathh,sizeof(pathh))!=NULL)
			printf("%s\n",pathh);
		else
			perror("myshell");
	}
	else if(strcmp(args[0],quitt)==0)
		exit(0);
	else
		printf("command not found\n");
}


