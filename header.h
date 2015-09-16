/* file containing all the required header files */
#ifndef header_h
#define header_h

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <limits.h>
#include <ctype.h>
#include <libgen.h>
#include <limits.h>
#include <dirent.h>
#define MAXX_INPUT 1024
#define DELIM " \t\r\n\a"
#define TOKEN_LIMIT 1000
#define PARSE_DELIM ";"
#define PIPE_DELIM "|"


extern int back_mark;
extern int position;
extern int pos;
extern int ind;
extern char home[1024];
extern char cd[3];
extern char **args;
extern char exitt[5];
extern char echoo[5];
extern char pwdd[4];
extern char pathh[1000];

void execute_cd(char **comm);
void statuss();
char **split_input1(char *line);
char **split_input2(char *line);
char **split_input3(char *line);
char *get_input(void);
void execute_internal(int fl);
void loop_pipe(char **args);
int pipe_func(int in, int out, char *line);

#endif
