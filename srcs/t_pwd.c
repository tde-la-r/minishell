#include <stdio.h>
#include <unistd.h>
int	main(void)
{
	printf("%s", getcwd(NULL, 0));
}
