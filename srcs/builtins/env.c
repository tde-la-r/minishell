/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:52:29 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/30 20:47:54 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_vars(int fd, char **envp)
{
	int		i;
	bool	underscore_var_printed;

	underscore_var_printed = false;
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			if (!ft_strncmp("_=", envp[i], 2))
			{
				ft_putendl_fd("_=usr/bin/env", fd);
				underscore_var_printed = true;
				i++;
				continue ;
			}
			ft_putendl_fd(envp[i], fd);
		}
		i++;
	}
	if (!underscore_var_printed)
		ft_putendl_fd("_=usr/bin/env", fd);
}

int	ft_env(int fd, char **args, char **envp)
{
	if (args && args[1])
	{
		if (args[1][0] == '-' && args[1][1])
		{
			ft_dprintf(STDERR_FILENO, \
					"env: invalid option -- '%c'\n", args[1][1]);
			return (125);
		}
		ft_dprintf(STDERR_FILENO, "env: '%s': %s\n", args[1], strerror(ENOENT));
		return (127);
	}
	print_vars(fd, envp);
	return (0);
}
