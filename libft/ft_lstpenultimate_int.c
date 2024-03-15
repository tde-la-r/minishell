/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpenultimate_int.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:20:50 by amolbert          #+#    #+#             */
/*   Updated: 2024/01/19 14:53:52 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstpenultimate_int(t_lst *lst)
{
	if (!lst || !lst->next)
		return (0);
	while (lst->next->next)
		lst = lst->next;
	return (lst);
}
