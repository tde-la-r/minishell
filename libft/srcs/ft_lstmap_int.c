/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:08:15 by amolbert          #+#    #+#             */
/*   Updated: 2024/01/19 14:56:44 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstmap_int(t_lst *lst)
{
	t_lst	*new;
	t_lst	*start;

	if (!lst)
		return (NULL);
	start = 0;
	while (lst)
	{
		new = ft_lstnew_int(lst->content);
		if (!new)
		{
			ft_lstclear_int(&start);
			return (NULL);
		}
		ft_lstadd_back_int(&start, new);
		lst = lst->next;
	}
	return (start);
}
