/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:43:00 by amolbert          #+#    #+#             */
/*   Updated: 2024/01/17 17:15:21 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_base(char *base_l, char *base_u)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 10)
	{
		base_l[i] = '0' + i;
		base_u[i] = '0' + i;
		i++;
	}
	while (j < 6)
	{
		base_l[i + j] = 'a' + j;
		base_u[i + j] = 'A' + j;
		j++;
	}
}

int	ft_isbase(char c, int base_len)
{
	char	base_u[16];
	char	base_l[16];
	int		i;

	i = 0;
	init_base(base_l, base_u);
	while (i < base_len && i < 16)
	{
		if (c == base_l[i] || c == base_u[i])
			return (1);
		i++;
	}
	return (0);
}
