/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:48:24 by amolbert          #+#    #+#             */
/*   Updated: 2024/01/19 14:53:38 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back_int(t_lst **lst, t_lst *new)
{
	t_lst	*node;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			node = ft_lstlast_int(*(lst));
			node->next = new;
		}
	}
}
