#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <libgen.h>
int main()
{
	FILE *fp;
	int myint;
	int BUFFERSIZE=80;
	char *buf=malloc(85);
	if((fp = fopen("/proc/1/status","r"))){
		while(fgets(buf, BUFFERSIZE, fp) != NULL){
			if(strstr(buf, "VmSize") != NULL){
				if (sscanf(buf, "%*s %d", myint) == 1){
					printf("VmSize: %d\n", myint);
				}
			}
		}
}
return 0;
}
