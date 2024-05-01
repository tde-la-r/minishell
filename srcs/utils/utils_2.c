/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:25:17 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/24 13:09:15 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_arraydup(char **array, int nbstr)
{
	int		i;
	char	**dup;

	dup = ft_calloc(sizeof(char *), nbstr + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (array[i] && i < nbstr)
	{
		dup[i] = ft_strdup(array[i]);
		if (!dup[i])
		{
			free_array(&dup);
			return (NULL);
		}
		i++;
	}
	return (dup);
}

char	*ft_getenv(const char *name, char **envp)
{
	char	*result;
	int		index;

	if (!name)
		return (NULL);
	index = find_env_index(name, envp, '=');
	if (index == -1)
		return (NULL);
	result = ft_strchr(envp[index], '=') + 1;
	return (result);
}

int	find_env_index(const char *to_test, char **envp, int c)
{
	int	i;
	int	len;
	int	len_arg;
	int	len_env;

	len_arg = 0;
	while (to_test[len_arg] != c && to_test[len_arg])
		len_arg++;
	i = 0;
	while (envp[i])
	{
		len_env = 0;
		while (envp[i][len_env] && envp[i][len_env] != '=')
			len_env++;
		len = ft_superior(len_arg, len_env);
		if (!ft_strncmp(to_test, envp[i], len))
			return (i);
		i++;
	}
	return (-1);
}

void	print_array(int fd, char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_putendl_fd(array[i], fd);
		i++;
	}
}

char	*check_color(t_minishell *data, char *prompt)
{
	char	*tmp;
	int		color;

	color = ft_abs(data->line_count) % 6;
	if (color == RE)
		tmp = ft_strjoin(RED, prompt);
	if (color == GR)
		tmp = ft_strjoin(GREEN, prompt);
	if (color == YE)
		tmp = ft_strjoin(YELLOW, prompt);
	if (color == BL)
		tmp = ft_strjoin(BLUE, prompt);
	if (color == PU)
		tmp = ft_strjoin(PURPLE, prompt);
	if (color == CY)
		tmp = ft_strjoin(CYAN, prompt);
	free(prompt);
	if (!tmp)
		error_exit(data, NULL, NULL, "malloc");
	return (tmp);
}
