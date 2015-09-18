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
int backexit=0;
int in_re;
int out_re;
char infile[1000];
char outfile[1000];
char **args;
int st[1000001];
char home[1024];
char cd[3] = {'c', 'd', '\0'};
char exitt[5]={'e','x','i','t','\0'};
char echoo[5]={'e','c','h','o','\0'};
char pinfoo[6]={'p','i','n','f','o','\0'};
char pwdd[4]={'p','w','d','\0'};
char quitt[5]={'q','u','i','t','\0'};
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
    		backexit=1; 
    		if(WIFEXITED(status))
    		{   				
    			printf("Process with id: %d terminated with exit status: ",pid);
    			printf("%d\n",WEXITSTATUS(status));
    		}
    		else
    			printf("Process not exited normally\n");
    		printprompt();
    		prompt2();
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
	int internal=0;
	char **ncomms;
	char **args_copy;
	char prompt[1000];
	char user[100],host[100];
	pid_t pid;
	int length;
	if(getcwd(home, sizeof(home))!=NULL)
	{	
		while(1)
		{
			backexit=0;
			flag=0;
	//		printf("<prachi@LenovoG500s");
			printprompt();
			for(i=0;i<1000;i++)
				prompt[i]='\0';
		
			if(getcwd(prompt, sizeof(prompt))!=NULL)
			{
				prompt2();
		
				input_str=get_input();
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
					internal=0;
					// args contains the "pipe" parsed commands 
					args=split_input3(ncomms[i]);
					if(args[0]!="\0");
					{
					//commmands whose binary files exists
						if(args[0][0]=='c' && args[0][1]=='d')
							internal=1;
						else if(args[0][0]=='e' && args[0][1]=='x' && args[0][2]=='i' && args[0][3]=='t')
							internal=1;
						else if(args[0][0]=='e' && args[0][1]=='c' && args[0][2]=='h' && args[0][3]=='o')
							internal=1;
						else if(args[0][0]=='p' && args[0][1]=='w' && args[0][2]=='d')
							internal=1;
						else if(args[0][0]=='q' && args[0][1]=='u' && args[0][2]=='i' && args[0][3]=='t')
							internal=1;
						if(internal!=1)
						{
							int len;
							len=strlen(args[0]);
							if(args[0][len-1]=='&')
								back_mark=1;
				//	signal(SIGCHLD,signalHandler);
							pid=fork();
							if(pid==0)
								loop_pipe(args);
							else if(pid<0)
								perror("myshell");
							else 
							{
								if(back_mark!=1)
									waitpid(pid,&status, WUNTRACED);
								else
								{
									signal(SIGCHLD,signalHandler);	
									printf("%d\n",pid);
										
								}
							}
						}
						else
						{
							args=split_input2(args[0]);
							// if built-in commands
							execute_internal(flag);
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
