/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectohexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:03:31 by amolbert          #+#    #+#             */
/*   Updated: 2023/11/09 21:51:09 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dectohexa(unsigned int n, char *index)
{
	int	len;

	len = ft_lennumhexa(n);
	if (n > 15)
		ft_dectohexa(n / 16, index);
	write(1, &index[n % 16], 1);
	return (len);
}
