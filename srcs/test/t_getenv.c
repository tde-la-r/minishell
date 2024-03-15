#include "stdlib.h"
#include "stdio.h"
int	main(int argc, char **argv)
{
	char *env_var;

	for (int i = 1 ; i < argc ; i++)
	{
		env_var = getenv(argv[i]);
		if (env_var)
			printf("%s\n", env_var);
	}
}
