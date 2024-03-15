/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:27:46 by amolbert          #+#    #+#             */
/*   Updated: 2023/12/16 10:13:12 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*array;

	array = (t_list *)malloc(sizeof(t_list));
	if (!array)
		return (NULL);
	array->content = content;
	array->next = NULL;
	return (array);
}
