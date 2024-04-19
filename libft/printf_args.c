/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:05:18 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/06 00:35:53 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_ptf(int fd, unsigned long number, char *base, int *count)
{
	if (number > ft_strlen(base) - 1)
		ft_putnbr_ptf(fd, number / ft_strlen(base), base, count);
	write(fd, base + (number % ft_strlen(base)), 1);
	(*count)++;
}

void	print_string_ptf(int fd, va_list *list, int *count)
{
	char	*str;

	str = va_arg(*list, char *);
	if (str)
	{
		while (*str)
		{
			write(fd, str, 1);
			(*count)++;
			str++;
		}
	}
	else
	{
		write(fd, "(null)", 6);
		*count += 6;
	}
}

void	print_integer_ptf(int fd, va_list *list, const char arg, int *count)
{
	int	integer;

	integer = va_arg(*list, int);
	if (arg == 'c')
	{
		write(fd, &integer, 1);
		(*count)++;
		return ;
	}
	if (integer == -2147483648)
	{
		write(fd, "-2147483648", 11);
		*count += 11;
		return ;
	}
	if (integer < 0)
	{
		integer = -integer;
		write (fd, "-", 1);
		(*count)++;
	}
	ft_putnbr_ptf(fd, integer, "0123456789", count);
}

void	print_u_int_ptf(int fd, va_list *list, const char to_print, int *count)
{
	unsigned int	u_integer;

	u_integer = va_arg(*list, unsigned int);
	if (to_print == 'x')
		ft_putnbr_ptf(fd, u_integer, "0123456789abcdef", count);
	if (to_print == 'X')
		ft_putnbr_ptf(fd, u_integer, "0123456789ABCDEF", count);
	if (to_print == 'u')
		ft_putnbr_ptf(fd, u_integer, "0123456789", count);
}

void	print_pointer_ptf(int fd, va_list *list, int *count)
{
	unsigned long	p;

	p = va_arg(*list, unsigned long);
	if (p)
	{
		write (fd, "0x", 2);
		*count += 2;
		ft_putnbr_ptf(fd, p, "0123456789abcdef", count);
	}
	else
	{
		write(fd, "(nil)", 5);
		*count += 5;
	}
}
