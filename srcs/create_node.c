/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:58:08 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/22 14:55:06 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_node_arg(t_minishell *data, char *line, int *i)
{
	int		len;
	t_line	*node;

	len = 0;
	while (line[*i + len] && !isifs(line[*i + len]) && !ismeta(line[*i + len]))
	{
		len = skip_quote('\"', line, *i + len) - *i;
		len = skip_quote('\'', line, *i + len) - *i;
		len++;
	}
	node = init_node(line, *i, len, 0);
	if (!node)
		error_exit(data, NULL, line, ERR_MALLOC);
	ft_lnadd_back(&data->line_lst, node);
	*i += len;
}

void	create_node_redir(t_minishell *data, char *line, int *i, int c)
{
	int		len;
	int		j;
	t_line	*node;

	len = 0;
	if (c == 'T' || c == 'I')
		j = 1;
	if (c == 'A' || c == 'H')
		j = 2;
	while (line[*i + j] && isifs(line[*i + j]))
		j++;
	while (line[*i + j + len] && !isifs(line[*i + j + len]) && \
	!ismeta(line[*i + j + len]))
	{
		len = skip_quote('\"', line, *i + j + len) - *i - j;
		len = skip_quote('\'', line, *i + j + len) - *i - j;
		len++;
	}
	node = init_node(line, *i + j, len, c);
	if (!node)
		error_exit(data, NULL, line, ERR_MALLOC);
	ft_lnadd_back(&data->line_lst, node);
	*i += len + j;
}

void	create_node_pipe(t_minishell *data, char *line, int *i, int c)
{
	t_line	*node;

	node = init_node(line, *i, 0, c);
	if (!node)
		error_exit(data, NULL, line, ERR_MALLOC);
	ft_lnadd_back(&data->line_lst, node);
	(*i)++;
}
