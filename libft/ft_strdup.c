/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:03:31 by amolbert          #+#    #+#             */
/*   Updated: 2023/11/02 11:12:24 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	char	*s;
	int		i;
	size_t	dst_len;

	i = 0;
	s = (char *)src;
	dst_len = ft_strlen(s);
	dst = (char *)malloc(sizeof(char) * (dst_len + 1));
	if (dst == NULL)
		return (NULL);
	while (s[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
