/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:01:14 by amolbert          #+#    #+#             */
/*   Updated: 2023/12/16 10:13:25 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*array;

	if (lst)
	{
		while (*lst)
		{
			array = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = array;
		}
	}
}
