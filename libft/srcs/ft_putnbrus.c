/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:03:31 by amolbert          #+#    #+#             */
/*   Updated: 2023/11/09 21:07:05 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrus(unsigned int n)
{
	int	len;

	len = ft_lennumus(n);
	if (n > 9)
		ft_putnbrus(n / 10);
	ft_putchar((n % 10) + '0');
	return (len);
}
