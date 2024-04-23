/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:12:28 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/23 14:55:56 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_dquote(char **envp, char **new_envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			if (add_first_quote(envp, new_envp, i))
				return (EXIT_FAILURE);
			if (add_second_quote(envp, new_envp, i))
				return (EXIT_FAILURE);
		}
		else
		{
			new_envp[i] = ft_strdup(envp[i]);
			if (!new_envp[i])
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	sort_envp(char **new_envp)
{
	int		i;
	int		len_1;
	int		len_2;
	int		len;
	char	*tmp;

	i = 0;
	while (new_envp[i])
	{
		len_1 = ft_strlen(new_envp[i]);
		len_2 = ft_strlen(new_envp[i + 1]);
		len = ft_superior(len_1, len_2);
		if (ft_strncmp(new_envp[i], new_envp[i + 1], len) > 0)
		{
			tmp = new_envp[i];
			new_envp[i] = new_envp[i + 1];
			new_envp[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

static void	delete_var(char **new_envp)
{
	int	i;

	i = 0;
	while (new_envp[i])
	{
		if (!ft_strncmp(new_envp[i], "_=", 2))
		{
			free(new_envp[i]);
			while (new_envp[i])
			{
				new_envp[i] = new_envp[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}

static int	add_declare(char **new_envp)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (new_envp[i])
	{
		tmp = ft_strdup(new_envp[i]);
		if (!tmp)
			return (EXIT_FAILURE);
		tmp2 = ft_strjoin("declare -x ", tmp);
		free(tmp);
		if (!tmp2)
			return (EXIT_FAILURE);
		free(new_envp[i]);
		new_envp[i] = tmp2;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	export_no_arg(char **envp, char **new_envp, int nbenv, int fd)
{
	int	i;

	i = 0;
	new_envp = ft_calloc(sizeof(char *), nbenv + 1);
	if (!new_envp)
		return (EXIT_FAILURE);
	if (add_dquote(envp, new_envp))
	{
		free_array(&new_envp);
		return (EXIT_FAILURE);
	}
	sort_envp(new_envp);
	delete_var(new_envp);
	if (add_declare(new_envp))
	{
		free_array(&new_envp);
		return (EXIT_FAILURE);
	}
	print_array(fd, new_envp);
	free_array(&new_envp);
	return (EXIT_SUCCESS);
}
