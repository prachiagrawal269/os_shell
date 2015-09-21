#include "header.h"

// creating array containing name of signals corresponding to their number

/*void createsignal()
{
	int sig,i,len;
	char *str;
	char **temp;
	char c;
    for (sig = 1; sig < NSIG; sig++)
    {
    	printf("entered\n");
        str = strdup(sys_siglist[sig]);
     //   temp[sig]=str;
       // signum_to_name[sig]=str;
        len=strlen(str);
        for (i = 0; i<len; i++)
    	{	
    		c=str[i];
    	//	printf("c : %c\n",c);
    		str[i]=toupper(c);
    	}
    	printf("yes\n");
    	printf("%s\n",str);
    //	signum_to_name[sig]=str;
    //	printf("copied\n");
    //	signum_to_name[sig]='\0';
  //      strcpy(signum_to_name[sig],str);
    }
} */

void childhandler(int signal)
{
	int status,i;
	pid_t pid;
	if (signal==SIGCHLD) 
	{//	sleep(0);
		while((pid=waitpid(-1, &status,WNOHANG))> 0)
		{	//printf("\n");
			
			for(i=0;i<back_index;i++)
			{
				if((back_job[i].pro_id)==pid)
				{
					back_job[i].back_active=0;
				//	printf("zeroed: %d %d\n",back_job[i].pro_id,back_job[i].back_active);
					break;
				}
			}	
			if(WIFEXITED(status))
			{   			
				printf("\n%s with pid %d terminated with exit status: ",back_job[i].processname,pid);
				printf("%d\n",WEXITSTATUS(status));
			}
			else
			{
				if(WIFSIGNALED(status))
				{ 
					if(over_mark!=1)
						printf("\n%s with pid %d exited due to the signal no. %d\n",back_job[i].processname ,pid,WTERMSIG(status));
				}
			}

			printprompt();
		}
	}	
}
