/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:19:25 by amolbert          #+#    #+#             */
/*   Updated: 2023/11/07 17:17:34 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*temp;

	if (!src && !dest && n)
		return (dest);
	i = 0;
	temp = dest;
	while (i < n)
	{
		*temp = *(char *)src;
		temp++;
		src++;
		i++;
	}
	return (dest);
}
