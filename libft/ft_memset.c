/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:22:22 by amolbert          #+#    #+#             */
/*   Updated: 2023/10/30 17:12:27 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	count;
	char	*p;

	p = s;
	count = 0;
	while (count < n)
	{
		*p = (char) c;
		p++;
		count++;
	}
	return (s);
}
