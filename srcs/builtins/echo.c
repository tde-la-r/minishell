/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:55:41 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/08 16:47:28 by tde-la-r         ###   ########.fr       */
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

int	ft_echo(int fd, char **args)
{
	int	i;
	int	opt;

	i = 1;
	opt = check_opt(args[i]);
	while (args[i] && check_opt(args[i]))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!opt)
		ft_putstr_fd("\n", fd);
	return (0);
}
