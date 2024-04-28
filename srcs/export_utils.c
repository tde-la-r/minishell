/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:15:03 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/29 01:16:19 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_first_quote(char **envp, char **new_envp, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (envp[i][j] && envp[i][j] != '=')
		j++;
	j++;
	tmp = ft_substr(envp[i], 0, j);
	if (!tmp)
		return (EXIT_FAILURE);
	new_envp[i] = ft_strjoin(tmp, "\"");
	free(tmp);
	if (!new_envp[i])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	add_second_quote(char **envp, char **new_envp, int i)
{
	char	*tmp;
	char	*tmp_2;

	tmp_2 = ft_strchr_next(envp[i], '=');
	tmp = ft_strjoin(new_envp[i], tmp_2);
	if (!tmp)
		return (EXIT_FAILURE);
	free(new_envp[i]);
	new_envp[i] = ft_strjoin(tmp, "\"");
	free(tmp);
	if (!new_envp[i])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*char	*select_content(char *var)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(var);
	tmp = NULL;
	while (var[i] && var[i] != '=')
		i++;
	tmp = ft_substr(var, i + 1, len);
	free(var);
	if (!tmp)
		return (NULL);
	return (tmp);
}*/

int	modify_var(char **new_envp, char *dup_var, int index, int operator)
{
	char	*to_add;
	char	*tmp;

	if (operator == '\0')
		free(dup_var);
	else if (operator == '=')
	{
		free(new_envp[index]);
		new_envp[index] = dup_var;
	}
	else
	{
		if (ft_strchr(new_envp[index], '='))
			to_add = ft_strchr_next(dup_var, '=');
		else
			to_add = ft_strchr(dup_var, '=');
		tmp = ft_strjoin(new_envp[index], to_add);
		free(dup_var);
		if (!tmp)
			return (EXIT_FAILURE);
		free(new_envp[index]);
		new_envp[index] = tmp;
	}
	return (EXIT_SUCCESS);
}
