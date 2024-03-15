#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

int	read_data(DIR *directory)
{
	struct dirent	*dir_data;

	errno = 0;
	dir_data = readdir(directory);
	if (!dir_data)
	{
		if (!errno)
		{
			printf("end of directory stream\n\n");
			return (1);
		}
		else
		{
			perror("readdir");
			return (-1);
		}
	}
	printf("name : %s\n", dir_data->d_name);
	printf("inode number : %lu\n", dir_data->d_ino);
	printf("current position : %ld\n", dir_data->d_off);
	printf("size : %d\n", dir_data->d_reclen);
	printf("type : %d\n", dir_data->d_type);
	printf("\n");
	return (0);
}

int	main(int argc, char **argv)
{
	DIR	*directory;
	int	red;

	for (int i = 1 ; i < argc ; i++)
	{
		directory = opendir(argv[i]);
		if (!directory)
		{
			perror(argv[i]);
			return (1);
		}
		red = read_data(directory);
		while (!red)
			red = read_data(directory);
		closedir(directory);
		if (red == -1)
			return (1);
	}
	return (0);
}
