#include "header.h"

// prints prompt
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
	fflush( stdout );
}

//get input from the user
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
			// reallocating the buffer for more input
			buffer=realloc(buffer, max_input);
			if(!buffer)
			{
				fprintf(stderr, "myshell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}