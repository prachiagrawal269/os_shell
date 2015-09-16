#include "header.h"
#define MAXX_INPUT 1024
#define DELIM " \t\r\n\a"
#define TOKEN_LIMIT 1000
#define PARSE_DELIM ";"
<<<<<<< HEAD
#define HOST_NAME_MAXX 255
#define LOGIN_NAME_MAXX 50
=======
>>>>>>> ede764676e6e5527378b05c16c82a2395d3df4d1
char *prompt;
int flag;
char *input_str;
int back_mark=0;
int pos=0;
<<<<<<< HEAD
int ind=0;
int position=0;
char **args;
char home[1024];
char cd[3] = {'c', 'd', '\0'};
char exitt[5]={'e','x','i','t','\0'};
char echoo[5]={'e','c','h','o','\0'};
char pwdd[4]={'p','w','d','\0'};
char pathh[1000];

=======
int position=0;
char home[1024];
>>>>>>> ede764676e6e5527378b05c16c82a2395d3df4d1
int main(int argc, char *argv[])
{
	int status,i,l,j,ii;
	int start,end;
	char *input_str;
	int l1,l2;
	char c;
	char **ncomms;
<<<<<<< HEAD
//	char **args;
	char prompt[1000];
	char user[100],host[100];
	pid_t pid;
=======
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
>>>>>>> ede764676e6e5527378b05c16c82a2395d3df4d1
	int length;
	if(getcwd(home, sizeof(home))!=NULL)
	{	//printf("%s\n",home);
	while(1)
	{
		flag=0;
<<<<<<< HEAD
//		printf("<prachi@LenovoG500s");
	char hostname[HOST_NAME_MAXX+1];
	char login[LOGIN_NAME_MAXX];

	// null-terminated regardless
	hostname[HOST_NAME_MAXX] = 0;
	login[LOGIN_NAME_MAXX-1] = 0;

	gethostname( hostname, HOST_NAME_MAXX );
	getlogin_r( login, LOGIN_NAME_MAXX );

	// <username>@<hostname>:)
	fprintf( stdout, "%s@%s:", login, hostname);
	fflush( stdout );
=======
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
>>>>>>> ede764676e6e5527378b05c16c82a2395d3df4d1
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
<<<<<<< HEAD
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
=======
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
>>>>>>> ede764676e6e5527378b05c16c82a2395d3df4d1
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
<<<<<<< HEAD
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
=======
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
>>>>>>> ede764676e6e5527378b05c16c82a2395d3df4d1
	else
	{	perror("myshell:");
		return EXIT_SUCCESS;
	}
	return 0;
}
