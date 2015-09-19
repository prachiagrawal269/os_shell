#include "header.h"
#define MAXX_INPUT 1024
#define DELIM " \t\r\n\a"
#define TOKEN_LIMIT 1000
#define PARSE_DELIM ";"

back_info back_job[50];
int back_index=0; 
int over_mark=0;
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
char copy[500];
int st[1000001];
char home[1024];
char cd[3] = {'c', 'd', '\0'};
char exitt[5]={'e','x','i','t','\0'};
char over[9]={'o','v','e','r','k','i','l','l','\0'};
char echoo[5]={'e','c','h','o','\0'};
char jobss[5]={'j','o','b','s','\0'};
char pinfoo[6]={'p','i','n','f','o','\0'};
char pwdd[4]={'p','w','d','\0'};
char quitt[5]={'q','u','i','t','\0'};
char pathh[1000];

int main(int argc, char *argv[])
{
	//struct rusage usage; 
	int status,i,l,j,ii,length,l1,l2,controld,start,end;;
	char *input_str;
	char c;
	int internal=0;
	char **ncomms;
	char **args_copy;
	char prompt[1000];
	char user[100],host[100];
	pid_t pid;
	controld=0;
	// handle sigint with hello
	signal(SIGINT, SIG_IGN);

	if(getcwd(home, sizeof(home))!=NULL)
	{	
		while(1)
		{
			position=0;
			backexit=0;
			//		back_index=0;
			flag=0;
			//		printf("<prachi@LenovoG500s");
			if(controld==0)
				printprompt();
			controld=0;
			for(i=0;i<1000;i++)
				prompt[i]='\0';

			if(getcwd(prompt, sizeof(prompt))!=NULL)
			{
				input_str=get_input();
				if(input_str[0]!='\0')
				{i=0;
				ncomms=split_input3(input_str,1);
				position=ind;
				while(position--)
				{
					internal=0;
					// args contains the "pipe" parsed commands 
					args=split_input3(ncomms[i],2);
					if(args[0]!="\0");
					{
						// check for built in commands
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
									signal(SIGCHLD, childhandler);
									strcpy(copy,args[0]);
									len=strlen(copy);
									copy[len-1]='\0';
									strcpy(back_job[back_index].processname,copy);
									//		printf("args: %s",args[0]);
									back_job[back_index].pro_id=pid;
									back_job[back_index].back_active=1;
									back_index++;
									back_mark=0;

										
									// storing background processes data(pid , name) into an array
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
				controld=1;
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