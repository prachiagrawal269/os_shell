#include "header.h"

// parsing with space as delimiter
char **split_input2(char *line)
{
	char **tokens=malloc(TOKEN_LIMIT * sizeof(char*));
	char *token;
	int token_limit;
	int i,len;
	in_re=0;
	out_re=0;
	append=0;
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
		else if(strcmp(token,"<")==0 )
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
		else if((strcmp(token,">")==0) || (strcmp(token,">>")==0))
		{
			if(strcmp(token,">")==0)
				out_re=1;
			else
				append=1;
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
		{
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
		}
		token=strtok(NULL, DELIM);
	}
	tokens[pos]=NULL;
	return tokens;
}

// f=1 for parsing with ";" as delimiter
// f=2 for parsing with "|" as delimiter

char **split_input3(char *line, int f)
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
	if(f==1)
		token=strtok(line, PARSE_DELIM);
	else if(f==2)
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
		if(f==1)
			token=strtok(NULL, PARSE_DELIM);
		else if(f==2)
			token=strtok(NULL, PIPE_DELIM);
	}
	tokens[ind]=NULL;
	return tokens;
}