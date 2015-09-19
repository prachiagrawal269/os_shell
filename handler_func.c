#include "header.h"

void childhandler(int signal)
{
	int status,i;
	pid_t pid;
	if (signal==SIGCHLD) 
	{//	sleep(0);
		while((pid=waitpid(-1, &status,WNOHANG))> 0)
		{	printf("\n");
			for(i=0;i<back_index;i++)
			{
				if((int)(back_job[i].pro_id)==pid)
				{
					back_job[i].back_active=0;
					break;
				}
			}
			if(WIFEXITED(status))
			{   				
				printf("Process with pid %d terminated with exit status: ",pid);
				printf("%d\n",WEXITSTATUS(status));
			}
			else
			{
				if(WIFSIGNALED(status))
				{ 
				//	printf("over: %d\n",over_mark);
					if(over_mark!=1)
						printf("Process with pid %d exited due to the signal no. %d\n", pid,WTERMSIG(status));
				}
			}

			printprompt();
		}
	}	
}
