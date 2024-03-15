/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:05:18 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/02/29 21:40:13 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_ptf(int n, unsigned long u, char *base, int *count)
{
	unsigned long	number;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		*count += 11;
		return ;
	}
	if (!u)
		number = n;
	if (!n)
		number = u;
	if (n < 0)
	{
		number = -n;
		write (1, "-", 1);
		(*count)++;
	}
	if (number > ft_strlen(base) - 1)
		ft_putnbr_ptf(0, number / ft_strlen(base), base, count);
	write(1, base + (number % ft_strlen(base)), 1);
	(*count)++;
}

void	print_string_ptf(va_list *list, int *count)
{
	char	*str;

	str = va_arg(*list, char *);
	if (str)
	{
		while (*str)
		{
			write(1, str, 1);
			(*count)++;
			str++;
		}
	}
	else
	{
		write(1, "(null)", 6);
		*count += 6;
	}
}

void	print_integer_ptf(va_list *list, const char **to_print, int *count)
{
	int	integer;

	integer = va_arg(*list, int);
	if (**to_print == 'c')
	{
		write(1, &integer, 1);
		(*count)++;
	}
	if (**to_print == 'd' || **to_print == 'i')
		ft_putnbr_ptf(integer, 0, "0123456789", count);
}

void	print_u_int_ptf(va_list *list, const char **to_print, int *count)
{
	unsigned int	u_integer;

	u_integer = va_arg(*list, unsigned int);
	if (**to_print == 'x')
		ft_putnbr_ptf(0, u_integer, "0123456789abcdef", count);
	if (**to_print == 'X')
		ft_putnbr_ptf(0, u_integer, "0123456789ABCDEF", count);
	if (**to_print == 'u')
		ft_putnbr_ptf(0, u_integer, "0123456789", count);
}

void	print_pointer_ptf(va_list *list, int *count)
{
	unsigned long	p;

	p = va_arg(*list, unsigned long);
	if (p)
	{
		write (1, "0x", 2);
		*count += 2;
		ft_putnbr_ptf(0, p, "0123456789abcdef", count);
	}
	else
	{
		write(1, "(nil)", 5);
		*count += 5;
	}
}
