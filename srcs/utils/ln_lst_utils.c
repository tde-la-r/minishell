/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ln_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:19:37 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/17 20:42:54 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_line	*ft_lnlast(t_line *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lnadd_back(t_line **lst, t_line *new)
{
	t_line	*node;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			node = ft_lnlast(*(lst));
			new->prev = node;
			node->next = new;
		}
	}
}

void	ft_lndelone(t_line *lst)
{
	if (!lst)
		return ;
	free(lst->str);
	lst->index = 0;
	lst->type = 0;
	free(lst);
}

void	ft_lnclear(t_line **lst)
{
	t_line	*node;

	if (lst)
	{
		while (*lst)
		{
			node = (*lst)->next;
			ft_lndelone(*lst);
			*lst = NULL;
			(*lst) = node;
		}
	}
}

t_line	*ft_lnnew(int index, int type, char *str, t_line *prev)
{
	t_line	*new;

	new = ft_calloc(sizeof(*new), 1);
	if (!new)
		return (NULL);
	new->index = index;
	new->type = type;
	new->str = str;
	new->prev = prev;
	return (new);
}
