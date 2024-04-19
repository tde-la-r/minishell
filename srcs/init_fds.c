/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:29:30 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/17 17:35:36 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_ambiguous_redir(t_minishell *data, t_cmd *new, t_line *redir)
{
	char	**array;
	int		i;

	if (redir->type == EL_HEREDOC)
		return (false);
	array = split_ifs(redir->str);
	if (!array)
		error_exit(data, new, NULL, ERR_MALLOC);
	i = 0;
	while (array[i])
		i++;
	free_array(&array);
	if (i == 1)
	{
		find_quote(redir->str);
		return (false);
	}
	ft_putendl_fd(ERR_AMB_REDIR, STDERR_FILENO);
	return (true);
}

static void	close_prev_fd(int redir, t_cmd *new)
{
	if (redir == EL_HEREDOC || redir == EL_INFILE)
	{
		if (new->fd_in != STDIN_FILENO)
			close(new->fd_in);
	}
	else if (new->fd_out != STDOUT_FILENO)
		close(new->fd_out);
}

t_cmd	*fds_redir(t_minishell *data, t_cmd *new, t_line *redir)
{
	if (new->fd_in == -1 || new->fd_out == -1)
		return (new);
	if (check_ambiguous_redir(data, new, redir))
	{
		close_prev_fd(EL_INFILE, new);
		new->fd_in = -1;
		return (new);
	}
	close_prev_fd(redir->type, new);
	if (redir->type == EL_HEREDOC)
		new->fd_in = create_here_doc(redir->str, data, new);
	if (new->fd_in == HEREDOC_SIGNALED)
		return (new);
	if (redir->type == EL_INFILE)
		new->fd_in = open(redir->str, O_RDONLY);
	if (redir->type == EL_OUT_A)
		new->fd_out = open(redir->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (redir->type == EL_OUT_T)
		new->fd_out = open(redir->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (new->fd_out == -1 || new->fd_in == -1)
		perror(redir->str);
	return (new);
}

t_cmd	*create_next_node(t_minishell *data, t_cmd **new, t_line *pipe_node)
{
	int		fd_pipe[2];
	int		nb_args;
	t_cmd	*next_node;

	if (pipe(fd_pipe) == -1)
		error_exit(data, NULL, NULL, ERR_PIPE);
	if ((*new)->args && (*new)->fd_out == STDOUT_FILENO)
		(*new)->fd_out = fd_pipe[1];
	else
		close(fd_pipe[1]);
	nb_args = find_nb_args(pipe_node->next);
	next_node = ft_cmdnew(fd_pipe[0], nb_args);
	if (!next_node)
	{
		close(fd_pipe[0]);
		error_exit(data, NULL, NULL, ERR_MALLOC);
	}
	return (next_node);
}

t_cmd	*ft_cmdnew(int cmd_in, int nb_args)
{
	t_cmd	*node;

	node = ft_calloc(sizeof(t_cmd), 1);
	if (!node)
		return (NULL);
	node->fd_in = cmd_in;
	node->fd_out = STDOUT_FILENO;
	node->args = ft_calloc(sizeof(char *), nb_args + 1);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	return (node);
}
