#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void    error(char *err)
{
        perror(err);
        exit (1);
}

int main (void)
{
        char *cwd = getcwd(NULL, 0);
        unlink(cwd);
        error("getcwd");
}       
