/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_stat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:54:35 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/04 15:20:53 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

void	error(char *err)
{
	perror(err);
	exit (1);
}

int	main(int argc, char **argv)
{
	struct stat	sb;

	for (int i = 1 ; i < argc ; i++)
	{
		if (stat(argv[i], &sb) == -1)
			error("stat");
		printf("ID of containing device:  [%jx,%jx]\n", (uintmax_t) major(sb.st_dev), \
				(uintmax_t) minor(sb.st_dev));
		printf("File type:                ");
		switch (sb.st_mode & S_IFMT) 
		{
			case S_IFBLK:  printf("block device\n");            break;
			case S_IFCHR:  printf("character device\n");        break;
			case S_IFDIR:  printf("directory\n");               break;
			case S_IFIFO:  printf("FIFO/pipe\n");               break;
			case S_IFLNK:  printf("symlink\n");                 break;
			case S_IFREG:  printf("regular file\n");            break;
			case S_IFSOCK: printf("socket\n");                  break;
			default:       printf("unknown?\n");                break;
		}
		printf("I-node number:            %ju\n", (uintmax_t) sb.st_ino);
		printf("Mode:                     %jo (octal)\n", \
				(uintmax_t) sb.st_mode);
		printf("Link count:               %ju\n", (uintmax_t) sb.st_nlink);
		printf("Ownership:                UID=%ju   GID=%ju\n", \
				(uintmax_t) sb.st_uid, (uintmax_t) sb.st_gid);
		printf("Preferred I/O block size: %jd bytes\n", \
				(intmax_t) sb.st_blksize);
		printf("File size:                %jd bytes\n", \
				(intmax_t) sb.st_size);
		printf("Blocks allocated:         %jd\n", \
				(intmax_t) sb.st_blocks);
		printf("Last status change:       %s", ctime(&sb.st_ctime));
		printf("Last file access:         %s", ctime(&sb.st_atime));
		printf("Last file modification:   %s", ctime(&sb.st_mtime));
		exit(EXIT_SUCCESS);
	}
}
