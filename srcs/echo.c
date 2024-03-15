/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:55:41 by amolbert          #+#    #+#             */
/*   Updated: 2024/03/15 15:59:04 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_opt(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0' && i > 1)
		return (1);
	return (0);
}

int	ft_echo(char **args)
{
	int	i;
	int	opt;

	i = 1;
	opt = check_opt(args[i]);
	while (args[i] && check_opt(args[i]))
		i++;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!opt)
		printf("\n");
	return (0);
}

int	main(int argc, char **argv)
{
	(void) argc;
	ft_echo(argv);
}
