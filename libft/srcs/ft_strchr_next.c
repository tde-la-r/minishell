/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_next.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:42:37 by amolbert          #+#    #+#             */
/*   Updated: 2024/01/15 16:58:58 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_next(const char *s, int c)
{
	char	*t;
	int		i;

	t = (char *) s;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (t + i + 1);
		i++;
	}
	if (!c)
		return (t + i);
	return (NULL);
}
