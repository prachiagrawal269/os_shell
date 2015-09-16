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
int ind=0;
int exit_status;
int position=0;
char **args;
//int count=0;
int st[1000001];
char home[1024];
char cd[3] = {'c', 'd', '\0'};
char exitt[5]={'e','x','i','t','\0'};
char echoo[5]={'e','c','h','o','\0'};
char pwdd[4]={'p','w','d','\0'};
char pathh[1000];

void signalHandler(int signal)
{
	int status;
	pid_t pid;

	if (signal==SIGCHLD) 
	{
		while ((pid=waitpid(-1, &status, WNOHANG))> 0)
    		{
    			printf("\n");
    			statuss(pid,0); 
    			if(WIFEXITED(status))
    			{
    			//	pid_t pid2 = wait3(&status, WNOHANG, (struct rusage *)NULL);
    				
    				printf("Process with id: %d terminated with exit status: ",pid);
    				printf("%d\n",WEXITSTATUS(status));
    				printprompt();
    			}
    			else
    			{
    			
    				printf("Process not exited normally\n");
    				printprompt();
    			}
    		}
	}
}

int main(int argc, char *argv[])
{
	//struct rusage usage; 
	int status,i,l,j,ii;
	int start,end;
	char *input_str;
	int l1,l2;
	char c;
	char **ncomms;
//	char **args;
	char prompt[1000];
	char user[100],host[100];
	pid_t pid;
	int length;
	if(getcwd(home, sizeof(home))!=NULL)
	{	//printf("%s\n",home);
	while(1)
	{
		flag=0;
//		printf("<prachi@LenovoG500s");
		printprompt();
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
		//	printf("input: %s\n",input_str);
			ncomms=split_input1(input_str);
		//	printf("ncomm: %s\n",ncomms[0]);
	// if args[0]=='cd' or 'pwd' or 'echo'
	// then go for executing
	// the built-in commands
//i=0; 		
		//	printf("position: %d\n",position);
			i=0;
 			while(position--)
			{
				// args contains the "pipe" parsed commands 
				args=split_input3(ncomms[i]);

				if(ind>1)
				{
					//  piping exists
					pid=fork();
					if(pid==0)
					{
						loop_pipe(args);
						printf("piping executed succesfully\n");
					}
					else
						wait(NULL);
				}
				else
				{
					args=split_input2(args[0]);
				if(args[0]!="\0");
				{
				//commmands whose binary files exists
				if(strcmp(args[0],cd)!=0 && (strcmp(args[0],exitt)!=0) && strcmp(args[0],echoo)!=0 && strcmp(args[0],pwdd)!=0)
				{
			//	signal(SIGCHLD,signalHandler);
					pid=fork();
					if(pid==0)
					{
					// if the process is a background process
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
								statuss(ii,1);
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
				//		printf("ppid: %d\n",pid);
						
						if(back_mark!=1)
							waitpid(pid,&status, WUNTRACED);
						else
						{
							// if it is a background process then don't wait for the child process to execute
							back_mark=0;
					//		signal(SIGHUP,SIG_IGN);
							signal(SIGCHLD,signalHandler);	
							printf("%d\n",pid);
								
						}
					}
				}
				else
				{
					// if built-in commands
					execute_internal(flag);
				}  
				}	
				}
				i++;
			}
		free(input_str);
		free(args);
		}
		else
			perror("myshell:");
	}
	}
	else
	{	perror("myshell:");
		return EXIT_SUCCESS;
	}
	return 0;
}
