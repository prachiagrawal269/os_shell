#include "header.h"
#define MAXX_INPUT 1024
#define DELIM " \t\r\n\a"
#define TOKEN_LIMIT 1000
#define PARSE_DELIM ";"
char *prompt;
int flag;
char *input_str;
int back_mark=0;
int pos=0;
int position=0;
char home[1024];
int main(int argc, char *argv[])
{
	int status,i,l,j,ii;
	int start,end;
	char *input_str;
	int l1,l2;
	char c;
	char **ncomms;
	char **args;
	char cd[3] = {'c', 'd', '\0'};
	char exitt[5]={'e','x','i','t','\0'};
	char echoo[5]={'e','c','h','o','\0'};
	char pwdd[4]={'p','w','d','\0'};
	char prompt[1000];
	char user[100],host[100];
	char pathh[1000];
	pid_t pid;
	FILE* pf1;
	FILE* pf2;
	int length;
	if(getcwd(home, sizeof(home))!=NULL)
	{	//printf("%s\n",home);
	while(1)
	{
		flag=0;
		pf1=popen("whoami","r");
		pf2=popen("hostname","r");
		printf("<prachi@LenovoG500s");
/*		while(fgets(user, 100, pf1))
		{
			l=strlen(user);
			user[l-1]='\0';
			fprintf(stdout, "%s",user);
			printf("@");
		}
		while(fgets(host, 100, pf2))
		{
			l=strlen(host);
			host[l-1]='\0';
			fprintf(stdout, "%s",host);
		} */
		for(i=0;i<1000;i++)
			prompt[i]='\0';
		if(getcwd(prompt, sizeof(prompt))!=NULL)
		{
			length=strcmp(home,prompt);
			if(length==0)
				printf("~");
			else if(length>0)
				printf("%s",prompt);
			else
			{
				l1=strlen(home);
				l2=strlen(prompt);
				printf("~");
				for(i=l1;i<l2;i++)
					printf("%c",prompt[i]);
			}
			printf(">");
			input_str=get_input();
			ncomms=split_input1(input_str);
// if args[0]=='cd' or 'pwd' or 'echo'
// then go for executing
// the built-in commands
			i=0; 		
 			while(position--)
			{
			args=split_input2(ncomms[i]);
			if(args[0]!="\0");
			{
				//commmands whose binary files exists
				if(strcmp(args[0],cd)!=0 && (strcmp(args[0],exitt)!=0) && strcmp(args[0],echoo)!=0 && strcmp(args[0],pwdd)!=0)
				{
					pid=fork();
					if(pid==0)
					{
					// if he process is a background process
						if(back_mark==1)
						{
							setpgid(0,0);
							if(execvp(args[0],args)<0)
								perror("myshell");
							exit(EXIT_FAILURE);
						}	
						else	
						{
							if(strcmp(args[0],"pinfo")==0)
							{
								if(args[1]==NULL)
									ii=getpid();
								else
									ii=atoi(args[1]);
								statuss(ii);
							}
							else
							{
								if(execvp(args[0],args)<0)
									perror("myshell");
								exit(EXIT_FAILURE);
							}
						}
					}
					else if(pid<0)
						perror("myshell");
					else 
					{
						if(back_mark!=1)
							waitpid(pid,&status, WUNTRACED);
						else
						{
							// if it is a background process then don't wait for the child process to execute
							signal(SIGHUP,SIG_IGN);
							printf("%d\n",pid);
						}
					}
				}
				else
				{
					//if the command is "cd"
					if(strcmp(args[0],cd)==0)
					{
						execute_cd(args);
						if(flag==1)
							chdir(home);
					}
					//if the command is exit
					else if(strcmp(args[0],exitt)==0)
						exit(0);
					//if the command is echo
					else if(strcmp(args[0],echoo)==0)
					{
						if(args[1]==NULL)
							continue;
						else
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

				}  
			}	i++;
			}
		free(input_str);
		free(args);
		pclose(pf1);
		pclose(pf2);
		}
		else
			perror("myshell:");
	}}
	else
	{	perror("myshell:");
		return EXIT_SUCCESS;
	}
	return 0;
}
