/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_index.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 23:20:44 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/12 16:22:57 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_index(const char *to_test, char **envp)
{
	int		i;
	int		len;
	int		len_arg;
	int		len_env;

	len_arg = 0;
	while (to_test[len_arg] != '=' && to_test[len_arg])
		len_arg++;
	i = 0;
	while (envp[i])
	{
		len_env = 0;
		while (envp[i][len_env] != '=')
			len_env++;
		len = ft_superior(len_arg, len_env);
		if (!ft_strncmp(to_test, envp[i], len))
			return (i);
		i++;
	}
	return (-1);
}
