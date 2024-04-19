/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:01:39 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/17 21:03:42 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quote(char quote, char *str, int i)
{
	if (str[i] != quote)
		return (i);
	if (i > 0)
		if (str[i - 1] == BACKSLASH_QUOTE)
			return (i);
	i++;
	while (str[i] != quote && str[i])
		i++;
	return (i);
}

bool	isifs(int c)
{
	int	i;

	i = 0;
	while (IFS[i])
	{
		if (c == IFS[i])
			return (true);
		i++;
	}
	return (false);
}

bool	isquote(int c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

bool	isredirection(t_line element)
{
	int	type;

	type = element.type;
	if (type == EL_INFILE || type == EL_HEREDOC)
		return (true);
	if (type == EL_OUT_A || type == EL_OUT_T)
		return (true);
	return (false);
}

void	free_array(char ***array)
{
	int	i;

	if (!*array)
		return ;
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}
