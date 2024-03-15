/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:48:24 by amolbert          #+#    #+#             */
/*   Updated: 2023/11/08 15:30:59 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*array;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			array = ft_lstlast(*(lst));
			array->next = new;
		}
	}
}
