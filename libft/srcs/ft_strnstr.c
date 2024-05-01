/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:19:35 by amolbert          #+#    #+#             */
/*   Updated: 2023/11/02 17:10:09 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b;
	size_t	i;
	size_t	j;
	size_t	little_len;

	b = (char *)big;
	i = 0;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return (b);
	while (i < len && big[i])
	{
		j = 0;
		while (i + j < len && b[i + j] == little[j] && little[j])
			j++;
		if (j == little_len)
			return (&b[i]);
		i++;
	}
	return (NULL);
}
