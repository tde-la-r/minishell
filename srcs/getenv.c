/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:28:07 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/12 16:23:36 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name, char **envp)
{
	char	*result;
	int		index;

	if (!name)
		return (NULL);
	index = find_env_index(name, envp);
	if (index == -1)
		return (NULL);
	result = ft_strchr(envp[index], '=') + 1;
	return (result);
}
