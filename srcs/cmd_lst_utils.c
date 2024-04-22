/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:05:22 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/22 17:40:08 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*ft_cmdlast(t_cmd *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*node;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			node = ft_cmdlast(*(lst));
			node->next = new;
		}
	}
}

void	ft_cmddelone(t_cmd *lst)
{
	if (!lst)
		return ;
	if (lst->fd_in > STDERR_FILENO)
		close(lst->fd_in);
	if (lst->fd_out > STDERR_FILENO)
		close(lst->fd_out);
	free_array(&lst->args);
	free(lst);
}

void	ft_cmdclear(t_cmd **lst)
{
	t_cmd	*node;

	if (lst)
	{
		while (*lst)
		{
			node = (*lst)->next;
			ft_cmddelone(*lst);
			*lst = NULL;
			(*lst) = node;
		}
	}
}

int	ft_cmdsize(t_cmd *list)
{
	int	i;

	if (!list)
		return (0);
	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}
