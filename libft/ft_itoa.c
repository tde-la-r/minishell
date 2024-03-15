/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:30:27 by amolbert          #+#    #+#             */
/*   Updated: 2023/11/06 22:45:44 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(int n)
{
	if (n == 0)
		return (1);
	return (count_len(n / 10) + 1);
}

static int	va_abs(int n)
{
	if (n > 0)
		return (n);
	return (-n);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		i;

	i = count_len(n) - 1;
	sign = (n < 0);
	if (n == 0)
		return (ft_strdup("0"));
	str = (char *)malloc((i + sign + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i + sign] = '\0';
	i--;
	while (i >= 0)
	{
		str[i + sign] = va_abs(n % 10) + 48;
		n /= 10;
		i--;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}
