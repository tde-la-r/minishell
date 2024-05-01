/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:34:06 by amolbert          #+#    #+#             */
/*   Updated: 2024/02/09 13:32:39 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_spaces_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}

int	ft_atoi_base(const char *str, int base)
{
	int	nbr;
	int	sign;
	int	i;

	sign = 1;
	nbr = 0;
	i = skip_spaces_sign(str, &sign);
	while (ft_isbase(str[i], 16))
	{
		nbr *= base;
		if (ft_isdigit(str[i]))
			nbr += str[i] - '0';
		else if (ft_islower(str[i]))
			nbr += str[i] - 'a' + 10;
		else
			nbr += str[i] - 'A' + 10;
		i++;
	}
	return (sign * nbr);
}
