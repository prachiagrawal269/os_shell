#include "header.h"

int in_re=0;
int out_re=0;

void loop_pipe(char **line)
{
	int i,fdin,fdout,in,fd[2];
	char **arg1;
	pid_t pid;
	in_re=0;
	out_re=0;
	in=0;
// for executing all the "piped" commands except the last one
	for(i=0;i<ind-1;i++)
	{
		pipe(fd);
		pipe_func(in, fd[1], line[i]);
		close(fd[1]);
		in=fd[0];
	}

	arg1=split_input2(line[i]);
	if(back_mark==1)
		setpgid(0,0);
//	printf("append: %d\n",append);
//	printf("out: %s\n",outfile);
		if(in!=0)
			dup2(in,STDIN_FILENO);
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
		if(append)
		{
			fdout=open(outfile,O_WRONLY|O_APPEND|O_CREAT,0666);
			append=0;
			dup2(fdout, STDOUT_FILENO);
			close(fdout);
		}

		if(strcmp(arg1[0],pinfoo)==0)
			execute_pinfo(arg1);
		else if(strcmp(arg1[0],jobss)==0)
			execute_jobs();
		else if(strcmp(arg1[0],over)==0)
			execute_overkill(-1);
		else if(strcmp(arg1[0],"kjob")==0)
			execute_kjob(atoi(arg1[1]),atoi(arg1[2]));
		else
		{
			if(execvp(arg1[0],arg1)<0)	
				perror("myshell");
			exit(EXIT_FAILURE);
		}
}

// this function is invoked to execute a command by creating a child process

int pipe_func(int in, int out, char *line)
{
	pid_t pid;
	int fdin,fdout;
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
		if(append)
		{
		//	printf("append\n");
			fdout=open(outfile,O_WRONLY|O_APPEND|O_CREAT,0666);
			append=0;
			dup2(fdout, STDOUT_FILENO);
			close(fdout);
		}
		if(strcmp(arg1[0],pinfoo)==0)
			execute_pinfo(arg1);
		else if(strcmp(arg1[0],jobss)==0)
			execute_jobs();
		else
		{
			if(execvp(arg1[0],arg1)<0)
				perror("myshell");
			exit(EXIT_FAILURE);
		}
	}
	return pid;
}