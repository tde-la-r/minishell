#include <stdio.h>
#include <stdlib.h>

int	main()
{
	char *ifs = getenv("IFS");
	printf("%s", ifs);
}
