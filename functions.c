#include "header.h"


int in_re=0;
int out_re=0;

// prints hostname and login
void printprompt()
{
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
}
// prints current directory
void prompt2()
{
	int i,l1,l2,length;
	char array[1000]="";
    char tilda[2]={'~','\0'};
    if(getcwd(array, sizeof(array))!=NULL)
				{
					length=strcmp(home,array);
					if(length==0)
						printf("~>");
					else if(length>0)
						printf("%s>",array);
					else
					{
						l1=strlen(home);
						l2=strlen(array);
						printf("~");
						for(i=l1;i<l2;i++)
							printf("%c",array[i]);
						printf(">");
					}
    			}
}

char *get_input(void)
{
	int c,position;
	int pos=0;
	int max_input;
	max_input=MAXX_INPUT;
	char *buffer=malloc(sizeof(char)*MAXX_INPUT);
	if(!buffer)
	{
		fprintf(stderr, "myshell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
	//	printf("\ntaking input\n");
	//	if(backexit!=1)
		c=getchar();
		if (c==EOF|| c=='\n')
		{
			buffer[pos]='\0';
			return buffer;
		}
		else
			buffer[pos]=c;
		pos++;
		if(pos>=max_input)
		{
			max_input=max_input*2;
			buffer=realloc(buffer, max_input);
			if(!buffer)
			{
				fprintf(stderr, "myshell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

char **split_input2(char *line)
{
	char **tokens=malloc(TOKEN_LIMIT * sizeof(char*));
	char *token;
	int token_limit;
	int i,len;
	in_re=0;
	out_re=0;
	token_limit=TOKEN_LIMIT;
	pos=0;
	if(!tokens)
	{
		fprintf(stderr,"myshell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token=strtok(line, DELIM);
	back_mark=0;
	while(token!=NULL)
	{
		if(strcmp(token,"&")==0)
		{
			back_mark=1;
			break;
		}
		else if(strcmp(token,"<")==0)
		{
			in_re=1;
			token=strtok(NULL, DELIM);
			if(token!=NULL)
			{
				strcpy(infile,token);
				token=strtok(NULL, DELIM);
				if(token!=NULL)
				{
					if(strcmp(token,">")==0)
					{
						out_re=1;
						token=strtok(NULL, DELIM);
						if(token!=NULL)
						{
							strcpy(outfile,token);
						}
					}
				}
			}
		}
		else if(strcmp(token,">")==0)
		{
			out_re=1;
			token=strtok(NULL, DELIM);
			if(token!=NULL)
			{
				strcpy(outfile,token);
				token=strtok(NULL, DELIM);
				if(token!=NULL)
				{
					if(strcmp(token,"<")==0)
					{
						in_re=1;
						token=strtok(NULL, DELIM);
						if(token!=NULL)
						{
							strcpy(infile,token);
						}
					}
				}
			}
		}
		else
		{tokens[pos]=token;
		pos++;	
		if (pos>=token_limit)
		{
			token_limit+=1000;
			tokens=realloc(tokens, token_limit * sizeof(char*));
			if(!tokens)
			{
				fprintf(stderr, "myshell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		}
		token=strtok(NULL, DELIM);
	}
	return tokens;
}

char **split_input3(char *line)
{
	char **tokens=malloc(TOKEN_LIMIT * sizeof(char*));
	char *token;
	int token_limit;
	token_limit=TOKEN_LIMIT;
	ind=0;
	if(!tokens)
	{
		fprintf(stderr,"myshell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token=strtok(line, PIPE_DELIM);
	back_mark=0;
	while(token!=NULL)
	{
		if(strcmp(token,"&")==0)
		{
			back_mark=1;
			break;
		}
		tokens[ind]=token;
		ind++;	
		if (ind>=token_limit)
		{
			token_limit+=1000;
			tokens=realloc(tokens, token_limit * sizeof(char*));
			if(!tokens)
			{
				fprintf(stderr, "myshell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token=strtok(NULL, PIPE_DELIM);
	}
	tokens[ind]=NULL;
	return tokens;
}

char **split_input1(char *line)
{
	char **tokens=malloc(TOKEN_LIMIT * sizeof(char*));
	char *token;
	int token_limit;
	token_limit=TOKEN_LIMIT;
	position=0;
	if(!tokens)
	{
		fprintf(stderr,"myshell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token=strtok(line, PARSE_DELIM);
	while(token!=NULL)
	{
		tokens[position]=token;
		position++;	
		if (position>=token_limit)
		{
			token_limit+=1000;
			tokens=realloc(tokens, token_limit * sizeof(char*));
			if(!tokens)
			{
				fprintf(stderr, "myshell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token=strtok(NULL, PARSE_DELIM);
	}
	tokens[position]=NULL;
	return tokens;
}


void loop_pipe(char **line)
{
	int i;
	char **arg1;
	pid_t pid;
	in_re=0;
	out_re=0;
	int fdin;
	int fdout;
	int in, fd[2];
	in=0;

	for(i=0;i<ind-1;i++)
	{
		pipe(fd);
		pipe_func(in, fd[1], line[i]);
		close(fd[1]);
		in=fd[0];
	}

	if(in!=0)
		dup2(in,STDIN_FILENO);

		arg1=split_input2(line[i]);
		if(back_mark==1)
		{
			setpgid(0,0);
			if(execvp(args[0],args)<0)
				perror("myshell");
			exit(EXIT_FAILURE);
		}	
		else
		{
			if(in_re)
			{
				fdin=open(infile,O_RDONLY);
				in_re=0;
				dup2(fdin, STDIN_FILENO);
				close(fdin);
			}
			if(out_re)
			{
				fdout=open(outfile,O_WRONLY|O_CREAT,0666);
				out_re=0;
				dup2(fdout, STDOUT_FILENO);
				close(fdout);
			}

			if(strcmp(arg1[0],pinfoo)==0)
				execute_pinfo(arg1);
			else
			{
				if(execvp(arg1[0],arg1)<0)	
					perror("myshell");
				exit(EXIT_FAILURE);
			}
		}

}

int pipe_func(int in, int out, char *line)
{
	pid_t pid;
	int fdin;
	int fdout;
	char **arg1;
	if((pid=fork())==0)
	{
		if(in!=0)
		{
			dup2(in,0);
			close(in);
		}
		if(out!=1)
		{
			dup2(out,1);
			close(out);
		}
		arg1=split_input2(line);
	
		if(in_re)
		{
			//		printf("inre\n");
			fdin=open(infile,O_RDONLY);
			in_re=0;
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		if(out_re)
		{
			fdout=open(outfile,O_WRONLY|O_CREAT,0666);
			out_re=0;
			dup2(fdout, STDOUT_FILENO);
			close(fdout);
		}

		if(strcmp(arg1[0],pinfoo)==0)
			execute_pinfo(arg1);
		else
		{
			if(execvp(arg1[0],arg1)<0)
				perror("myshell");
			exit(EXIT_FAILURE);
		}
	}
	return pid;
}

void execute_pinfo(char **line)
{
	int ii;
	if(line[1]==NULL)
		ii=getpid();
	else
		ii=atoi(line[1]);
	statuss(ii,1);

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




void statuss(int idd,int flag)
{
	// if flag==1, execute pinfo
	// if flag==0, print process name
	FILE *fp;
	int myint,ll,size,t;
	int len;
	char s1[1024];
	ll=11;
	char status[100];
	char name[1000];
	int BUFFERSIZE=1000;
	char *buf=malloc(10000);
	char path[1000];
	char pathexe[1000];
	sprintf(path,"/proc/%d/status",idd);
	sprintf(pathexe,"/proc/%d/smaps",idd);
	if((fp = fopen(path,"r")))
	{
		fgets(buf, BUFFERSIZE, fp);
		fgets(buf, BUFFERSIZE, fp);
		if(flag==1)
			sscanf(buf,"State:\t%s",status);
		else
		{
			sscanf(buf,"Name:\t%s",name);
		if(flag==0)
			printf("%s ",name);
		else
		{
			printf("Pid: %d\n",idd);
			printf("Status: %s\n",status);
		while(ll--)
		{
			fgets(buf, BUFFERSIZE, fp);
		}
		if(buf[0]=='V' && buf[1]=='m'&& buf[2]=='S' && buf[3]=='i')
		{
			sscanf(buf,"VmSize:\t%s",status);
			printf("Virtual Memory:	%s KB\n",status);
		}
		else
			printf("Virtual Memory: 0 KB\n");}
		if(fp=fopen(pathexe, "r"))
		{
			fgets(buf, BUFFERSIZE, fp);
			sscanf(buf,"%s[^\n]",s1);
			len=strlen(s1);
			t=0;
			for(t=0;t<len;t++)
			{
				if(s1[t]=='/')
					break;
			}
			if(t<len)
			{	
				while(t<len)
				{
					if(ispunct(s1[t])==0 && isalnum(s1[t])==0)
						break;
					else
						printf("%c",s1[t]);
					t++;
				}
			printf("\n");
			}
		}
		}
	}
}
