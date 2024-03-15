/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:28:27 by amolbert          #+#    #+#             */
/*   Updated: 2023/11/07 17:43:15 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*m;

	if (nmemb == 0 || size == 0)
	{
		m = malloc(0);
		if (!m)
			return (NULL);
		return (m);
	}
	if ((nmemb >= 2147483647 || size >= 2147483647
			|| (nmemb * size > 2147483647)))
		return (0);
	if (nmemb > 46341 && size > 46341)
		return (NULL);
	m = malloc((size) * (nmemb));
	if (!m)
		return (NULL);
	ft_bzero(m, nmemb * size);
	return (m);
}
