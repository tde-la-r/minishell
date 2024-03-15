/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:25:17 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/15 18:03:50 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_arraydup(char **array, int nb_env)
{
	char	**result;
	int		i;

	result = ft_calloc(sizeof(char *) , nb_env + 1);
	if (!result)
		error_exit(result, ERR_MALLOC);
	i = 0;
	while (array[i])
	{
		result[i] = ft_strdup(array[i]);
		if (!result[i])
			error_exit(result, ERR_MALLOC);
		i++;
	}
	return (result);
}
