/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:06:49 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/16 16:46:21 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_environment_variable(char **envp, int index, int *nb_envp)
{
	free(envp[index]);
	while (envp[index])
	{
		envp[index] = envp[index + 1];
		index++;
	}
	(*nb_envp)--;
}

int	ft_unset(char **args, char **envp, int *nb_envp)
{
	int		i;
	int		index;

	i = 1;
	while (args[i])
	{
		index = find_env_index(args[i], envp, '=');
		if (index >= 0)
			delete_environment_variable(envp, index, nb_envp);
		i++;
	}
	return (0);
}
