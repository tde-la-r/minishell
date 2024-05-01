/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:42:06 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/22 17:03:16 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_type(int c)
{
	int	type;

	if (c == '|')
		type = EL_PIPE;
	else if (c == 'I')
		type = EL_INFILE;
	else if (c == 'H')
		type = EL_HEREDOC;
	else if (c == 'A')
		type = EL_OUT_A;
	else if (c == 'T')
		type = EL_OUT_T;
	else
		type = EL_ARG;
	return (type);
}

t_line	*init_node(char *line, int i, int len, int c)
{
	static int	pos = 0;
	t_line		*tmp;

	tmp = malloc(sizeof(t_line));
	if (!tmp)
		return (NULL);
	tmp->index = pos;
	pos++;
	tmp->type = check_type(c);
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->str = ft_substr(line, i, len);
	if (!tmp->str)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
