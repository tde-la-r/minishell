/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:06:49 by amolbert          #+#    #+#             */
/*   Updated: 2024/03/15 15:57:10 by tde-la-r         ###   ########.fr       */
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
		index = find_env_index(args[i], envp);
		if (index > 0)
			delete_environment_variable(envp, index, nb_envp);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		nb_envp;
	char	**env_minishell;

	(void)argc;
	nb_envp = 0;
	while (envp[nb_envp])
		nb_envp++;
	env_minishell = ft_arraydup(envp, nb_envp);
	ft_env(env_minishell);
	printf("\n\n");
	ft_unset(argv, env_minishell, &nb_envp);
	ft_env(env_minishell);
	free_array(env_minishell);
}
