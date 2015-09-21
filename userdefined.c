#include "header.h"

// excute jobs command

void execute_jobs()
{
	int i,count;
	count=0;	
	for(i=0;i<back_index;i++)
	{
			//printf("%d %d\n",back_job[i].pro_id,back_job[i].back_active);
		if(back_job[i].back_active==1)
		{
			count++;
			printf("[%d]  ",count);
			printf("%s  ",back_job[i].processname);
			printf("[%d]\n",back_job[i].pro_id);
		}
	}
}

int execute_fg(int job_no)
{
	int count=0;
	int pid,status,i;
	for(i=0;i<back_index;i++)
	{
		if(back_job[i].back_active==1)
		{
			count++;
			if(count==job_no)
			{
				// bring process to foreground
				pid=back_job[i].pro_id;
				back_job[i].back_active=0;
				return pid;
			}
		}
	}
	if(i==back_index)
	{
		printf("Error: No such process exists\n");
		return -1;
	}
}

void execute_kjob(int job_no, int signum)
{
	int count=0;
	int pid,status,i;
	for(i=0;i<back_index;i++)
	{
		if(back_job[i].back_active==1)
		{
			count++;
			if(count==job_no)
			{
				pid=back_job[i].pro_id;
				// excute according to the signal
				kill(pid,signum);
				break;
			}

		}
	}
	if(i==back_index)
		printf("Error: No such process exists\n");
}

void execute_overkill(int pid)
{
//	pid_t pid;
	int i;
//	printf("entered overkill\n");
	if(pid==-1)
	{for(i=0;i<back_index;i++)
	{
		over_mark=0;
		if((back_job[i].back_active)==1)
		{
			over_mark=1;
			back_job[i].back_active=0;
			kill(back_job[i].pro_id, SIGKILL);
		}
	}
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

// execute pinfo which inturn calls the "stautuss" function
void execute_pinfo(char **line)
{
	int ii;
	if(line[1]==NULL)
		ii=getpid();
	else
		ii=atoi(line[1]);
	statuss(ii,1);

}