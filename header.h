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


extern int back_mark;
extern int position;
extern int pos;
extern char home[1024];

void execute_cd(char **comm);
void statuss();
char **split_input1(char *line);
char **split_input2(char *line);
char *get_input(void);
#endif
