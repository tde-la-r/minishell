/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:53:29 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/17 20:38:55 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_error_exit(t_minishell *data, char *err_msg)
{
	close_fds(data->cmd_lst);
	free_heap_memory(data, NULL, NULL, B_NO_DEL);
	if (errno == EBADF)
		exit (EXIT_FAILURE);
	perror(err_msg);
	exit (errno);
}

void	close_fds(t_cmd *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->fd_in > STDERR_FILENO)
			close(lst->fd_in);
		if (lst->fd_out > STDERR_FILENO)
			close(lst->fd_out);
		lst = lst->next;
	}
}

void	del_heredocs(char **heredocs)
{
	int	i;

	if (!heredocs)
		return ;
	i = 0;
	while (heredocs[i])
	{
		if (unlink(heredocs[i]) == -1)
			perror(ERR_UNLINK);
		i++;
	}
}

void	free_heap_memory(t_minishell *data, t_cmd *node, char *str, bool del)
{
	if (str)
		free(str);
	if (data)
	{
		free(data->prompt);
		if (data->line)
			free(data->line);
		free_array(&data->env);
		free_array(&data->paths);
		ft_cmdclear(&data->cmd_lst);
		ft_lnclear(&data->line_lst);
		if (del)
			del_heredocs(data->heredocs);
		free_array(&data->heredocs);
		free(data);
	}
	ft_cmddelone(node);
	rl_clear_history();
}

void	error_exit(t_minishell *data, t_cmd *node, char *str, char *err)
{
	if (data)
		close_fds(data->cmd_lst);
	free_heap_memory(data, node, str, B_DEL);
	if (err)
		perror(err);
	exit (errno);
}
