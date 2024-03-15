#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (int ac, char **av)
{
	char *pwd;
	int	pid;

	(void)ac;
	pwd = getcwd(NULL,0);
	printf("CWD1 : %s\n", pwd);
	free(pwd);
	if ((pid = fork()) == 0)
	{
		chdir(av[1]);
		pwd = getcwd(NULL,0);
		printf("CWD2 : %s\n", pwd);
		free(pwd);
		exit(0);
	}
	wait(NULL);
	pwd = getcwd(NULL,0);
	printf("CWD3 : %s\n", pwd);
	free(pwd);
}
