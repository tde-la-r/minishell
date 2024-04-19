/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:53:01 by amolbert          #+#    #+#             */
/*   Updated: 2024/03/22 18:41:18 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	if (s[i] == '\0')
		write(fd, "\n", 1);
	while (s[i])
	{
		write(fd, &s[i], 1);
		if (s[i + 1] == 0)
			write(fd, "\n", 1);
		i++;
	}
}
