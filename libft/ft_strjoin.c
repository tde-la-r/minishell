/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:09:40 by amolbert          #+#    #+#             */
/*   Updated: 2023/11/07 18:31:33 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	len_dest;

	len_dest = 0;
	while (dest[len_dest])
		len_dest++;
	i = 0;
	while (src[i])
	{
		dest[len_dest] = src[i];
		i++;
		len_dest++;
	}
	dest[len_dest] = 0;
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (ft_strdup(""));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!result)
		return (NULL);
	result[0] = 0;
	ft_strcat(result, s1);
	ft_strcat(result, s2);
	return (result);
}
