/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_chdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:36:23 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/06 14:37:41 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"

void	error(char *err)
{
	perror(err);
	exit (1);
}

int	main(int argc, char **argv)
{
	char *working_dir;

	working_dir = getcwd(NULL, 0);
	if (!working_dir)
		error("getcwd");
	printf("%s\n", working_dir);
	free(working_dir);
	for (int i = 1 ; i < argc ; i++)
	{
		if (chdir(argv[i]) == -1)
			error("chdir");
		working_dir = getcwd(NULL, 0);
		if (!working_dir)
			error("getcwd");
		printf("%s\n", working_dir);
		free(working_dir);
	}
}
