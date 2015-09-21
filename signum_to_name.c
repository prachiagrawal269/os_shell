#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void upcase(char *s)
{
    while (*s)
    {
        *s = toupper(*s);
        s++;        
    }
}

int main(void)
{    
    int sig;
    for (sig = 1; sig < NSIG; sig++)
    {
        char *str = strdup(sys_signame[sig]);
        if (!str)
            return -1;

        upcase(str);
        printf("%2d -> SIG%s\n", sig, str);

        free(str);
    }

    return 0;
}