/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointtohexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:03:31 by amolbert          #+#    #+#             */
/*   Updated: 2023/11/14 19:34:22 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pointtohexa(unsigned long long n, char *index, int start)
{
	int	len;

	if (!n)
	{
		ft_putstr("(nil)");
		return (5);
	}
	len = ft_lennumhexaull(n);
	if (start == 1)
	{
		len += 2;
		write(1, "0x", 2);
	}
	if (n > 15)
		ft_pointtohexa(n / 16, index, 0);
	if (n == 0)
		return (len);
	write(1, &index[n % 16], 1);
	return (len);
}
