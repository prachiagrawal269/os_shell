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
char **args;
//int count=0;
int st[1000001];
char home[1024];
char cd[3] = {'c', 'd', '\0'};
char exitt[5]={'e','x','i','t','\0'};
char echoo[5]={'e','c','h','o','\0'};
char pinfoo[6]={'p','i','n','f','o','\0'};
char pwdd[4]={'p','w','d','\0'};
char pathh[1000];

void signalHandler(int signal)
{
	int status,i,l1,l2,length;
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
    			//	pid_t pid2 = wait3(&status, WNOHANG, (struct rusage *)NULL);
    				
    				printf("Process with id: %d terminated with exit status: ",pid);
    				printf("%d\n",WEXITSTATUS(status));
    			//	printprompt();
    			}
    			else
    			{
    			
    				printf("Process not exited normally\n");
    			//	printprompt();
    			}

    			printprompt();
    	//		for(i=0;i<100;i++)
		//			prompt[i]='\0';
    			char array[1000]="";
    			char tilda[2]={'~','\0'};
    			if(getcwd(array, sizeof(array))!=NULL)
				{
				//	printf("entered if\n");
					length=strcmp(home,array);
				//	printf("home: %s\n",home);
				//	printf("array: %s\n",array);
				//	printf("len: %d\n",length);
					if(length==0)
					{
						printf("~");
						//printf('~');
					}
					else if(length>0)
						printf("%s",array);
					else
					{
						l1=strlen(home);
						l2=strlen(array);
						printf("~");
						for(i=l1;i<l2;i++)
							printf("%c",array[i]);
					}
		//	printf("yes arrow");
		
				printf(">");
    			}
    		//	else
    		//		printf("else\n");
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
//	char **args;
	char prompt[1000];
	char user[100],host[100];
	pid_t pid;
	int length;
	if(getcwd(home, sizeof(home))!=NULL)
	{	//printf("%s\n",home);
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
		//	printf("yes arrow");
		
			printf(">");
		//	if(backexit==1)
		//		continue;
		//	else
			input_str=get_input();
			printf("input: %s\n",input_str);
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

		/*		if(ind>1)
				{
					//  piping exists
					pid=fork();
					if(pid==0)
					{
						loop_pipe(args);
				//		printf("piping executed succesfully\n");
					}
					else
					{
				//		if(back_mark!=1)
							waitpid(pid,&status, WUNTRACED);
					}
					//	wait(NULL);
				}*/
		//		else
		//		{
				//	args_copy=split_input3(args[0]);
				//	printf("before: %s\n",args_copy[0]);
				//	args=split_input2(args[0]);
				//	printf("after: %s\n",args_copy[0]);
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
				if(internal!=1)
				{
					int len;
					len=strlen(args[0]);
						//		printf("len: %d\n",len);
						//		printf("char: %c",args[0][len-1]);
					if(args[0][len-1]=='&')
						back_mark=1;
			//	signal(SIGCHLD,signalHandler);
					pid=fork();
					if(pid==0)
					{
					// if the process is a background process
				/*		if(back_mark==1)
						{
							setpgid(0,0);
							if(execvp(args[0],args)<0)
								perror("myshell");
							exit(EXIT_FAILURE);
						}	*/
					//	else	
					//	{
						/*	if(args[0][0]=='p' && args[0][1]=='i' && args[0][2]=='n' && args[0][3]=='f' && args[0][4]=='o')
							{
								args=split_input2(args[0]);
								if(args[1]==NULL)
									ii=getpid();
								else
									ii=atoi(args[1]);
								statuss(ii,1);
							} */
						//	else
						//	{
							//	printf("else: %s\n",args_copy[0]);
							//	char **args_copy;
							//	args_copy=split_input2(args[0]);
							//	printf("back mark\n");
						
								loop_pipe(args);
							//	if(execvp(args[0],args)<0)
							//		perror("myshell");
							//	exit(EXIT_FAILURE);
						//	}
					//	}
					}
					else if(pid<0)
						perror("myshell");
					else 
					{
				//		printf("ppid: %d\n",pid);
				//		printf("parent\n");
						if(back_mark!=1)
							waitpid(pid,&status, WUNTRACED);
						else
						{
						//	printf("parent\n");
							// if it is a background process then don't wait for the child process to execute
						//	back_mark=0;
					//		signal(SIGHUP,SIG_IGN);
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
		//		}
				i++;
			}
		free(input_str);
		free(args);
	//	}
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
