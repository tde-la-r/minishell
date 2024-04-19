/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:23:00 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/19 10:59:01 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_nb_args(t_line *line_lst)
{
	int	i;

	i = 0;
	while (line_lst && line_lst->type != EL_PIPE)
	{
		if (line_lst->type == EL_ARG)
			i++;
		line_lst = line_lst->next;
	}
	return (i);
}

static void	add_arg_cmd(t_minishell *data, t_cmd **node, char *arg, int *i)
{
	(*node)->args[*i] = ft_strdup(arg);
	if (!(*node)->args[*i])
		error_exit(data, *node, NULL, ERR_MALLOC);
	(*i)++;
}

static t_cmd	*apply_pipe(t_minishell *data, t_cmd *node, \
t_line *index, int *i)
{
	ft_cmdadd_back(&data->cmd_lst, node);
	node = create_next_node(data, &node, index);
	*i = 0;
	return (node);
}

static int	check_element_type(t_minishell *data, t_cmd **node, \
t_line *index, int *i)
{
	if (index->type == EL_ARG)
		add_arg_cmd(data, node, index->str, i);
	if (isredirection(*index))
		*node = fds_redir(data, *node, index);
	if ((*node)->fd_in == HEREDOC_SIGNALED)
	{
		ft_cmddelone(*node);
		ft_cmdclear(&data->cmd_lst);
		data->exit = ECODE_SIGINT;
		return (1);
	}
	if (index->type == EL_PIPE)
		*node = apply_pipe(data, *node, index, i);
	return (0);
}

void	init_lst_cmd(t_minishell *data)
{
	int		nb_arg;
	t_cmd	*node;
	t_line	*index;
	int		i;

	i = 0;
	index = data->line_lst;
	nb_arg = find_nb_args(data->line_lst);
	node = ft_cmdnew(STDIN_FILENO, nb_arg);
	if (!node)
		error_exit(data, NULL, NULL, ERR_MALLOC);
	while (index)
	{
		if (check_element_type(data, &node, index, &i))
			return ;
		index = index->next;
	}
	ft_cmdadd_back(&data->cmd_lst, node);
}
