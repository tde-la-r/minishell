/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:52:29 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/19 18:38:35 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_bash_display(t_minishell *data, char *str)
{
	char	*display;

	display = ft_strdup("_=/usr/bin/env");
	if (!display)
		error_exit(data, NULL, NULL, ERR_MALLOC);
	free(str);
	return (display);
}

int	ft_env(t_minishell *data, int fd, char **args, char **envp)
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
		if (!ft_strncmp("_=", envp[i], 2))
			envp[i] = set_bash_display(data, envp[i]);
		ft_putendl_fd(envp[i], fd);
		i++;
	}
	return (0);
}
