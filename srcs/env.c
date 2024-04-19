/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:52:29 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/17 18:34:09 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(int fd, char **args, char **envp)
{
	int	i;

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
	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], fd);
		i++;
	}
	return (0);
}
