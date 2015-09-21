/* file containing all the required header files */
#ifndef header_h
#define header_h
#include "signal1.h"

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <limits.h>
#include <ctype.h>
#include <libgen.h>
#include <unistd.h> 
#include <signal.h> 
#include <limits.h>
#include <dirent.h>
#define MAXX_INPUT 1024
#define DELIM " \t\r\n\a"
#define TOKEN_LIMIT 1000
#define PARSE_DELIM ";"
#define PIPE_DELIM "|"
#define HOST_NAME_MAXX 255
#define LOGIN_NAME_MAXX 50

struct back_info{
	int pro_id;
	int back_active;
	char processname[200];
};
typedef struct back_info back_info;
back_info back_job[50];


//extern char signum_to_name[30][10];
extern int back_mark;
extern int position;
extern int pos;
extern int ind;
extern int backexit;
extern char home[1024];
extern char cd[3];
extern char **args;
extern char exitt[5];
extern char quitt[5];
extern char over[9];
extern char echoo[5];
extern char pinfoo[6];
extern char pwdd[4];
extern char jobss[5];
extern char pathh[1000];
extern int in_re;
extern int out_re;
extern int append;
extern char infile[1000];
extern char outfile[1000];
extern int back_index; 
extern int over_mark;
extern int shell_pgid;

void printprompt();
void execute_cd(char **comm);
void statuss(int idd, int flag);
char **split_input2(char *line);
char **split_input3(char *line, int f);
char *get_input(void);
void execute_internal(int fl);
void loop_pipe(char **args);
int pipe_func(int in, int out, char *line);
void execute_pinfo(char **line);
void execute_jobs();
void execute_overkill(int pid);
int execute_fg(int job_no);
void execute_kjob(int job_no, int signum);


#endif