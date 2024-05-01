/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:46:53 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/22 17:05:02 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*count_var_quotes(char *var)
{
	int		i;
	int		count;
	char	*dup;

	count = 0;
	i = 0;
	while (var[i])
	{
		if (var[i] == '\'' || var[i] == '\"')
			count++;
		i++;
	}
	dup = ft_calloc(sizeof(char), (i + count + 1));
	return (dup);
}

char	*insert_backslash_quotes(char *var)
{
	int		i;
	int		count;
	char	*dup;

	dup = count_var_quotes(var);
	if (!dup)
		return (NULL);
	count = 0;
	i = 0;
	while (var[i])
	{
		if (var[i] == '\'' || var[i] == '\"')
		{
			dup[i + count] = BACKSLASH_QUOTE;
			count++;
		}
		dup[i + count] = var[i];
		i++;
	}
	return (dup);
}

int	find_name_len(char *var)
{
	bool	digit_start;
	int		len;

	len = 0;
	digit_start = false;
	if (ft_isdigit(var[len]))
		digit_start = true;
	while ((ft_isalnum(var[len]) || var[len] == '_') && !digit_start)
		len++;
	if (!len)
		len = 1;
	return (len);
}
