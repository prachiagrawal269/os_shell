#include "header.h"


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
		tokens[pos]=token;
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
		token=strtok(NULL, DELIM);
	}
	tokens[pos]=NULL;
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
//	if(args[1]==NULL)
//		continue;
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

void statuss(int idd)
{
	FILE *fp;
	int myint,ll,size,t;
	int len;
	char s1[1024];
	ll=11;
	char status[100];
	int BUFFERSIZE=1000;
	char *buf=malloc(10000);
	char path[1000];
	char pathexe[1000];
	printf("Pid: %d\n",idd);
	sprintf(path,"/proc/%d/status",idd);
	sprintf(pathexe,"/proc/%d/smaps",idd);
	if((fp = fopen(path,"r"))){
		fgets(buf, BUFFERSIZE, fp);
		fgets(buf, BUFFERSIZE, fp);
		sscanf(buf,"State:\t%s",status);
//		printf("buff: %s",buf);	
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
			sscanf(buf,"%[^\n]",s1);
			len=strlen(s1);
			t=0;
		//	printf("s1: %s\n",s1);
			for(t=0;t<len;t++)
			{
				if(s1[t]=='/')
					break;
			}
			if(t<len)
			{	printf("Executable: ");
			//	printf("%c\n",s1[t]);
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
			else
				printf("hello\n");

//		len=readlink(pathexe, buf, sizeof(buf)-1);
//		if(len!=-1)
//		{
//			buf[len]='\0';
//			printf("Executable Path: %s\n", buf);
//		}
//		else
//			perror("readlink error\n");
	}
}

