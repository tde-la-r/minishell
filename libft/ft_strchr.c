/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:42:37 by amolbert          #+#    #+#             */
/*   Updated: 2024/01/15 14:48:39 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*t;
	int		i;

	t = (char *) s;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (t + i);
		i++;
	}
	if (!c)
		return (t + i);
	return (NULL);
}
