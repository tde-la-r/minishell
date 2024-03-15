/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:54:00 by amolbert          #+#    #+#             */
/*   Updated: 2023/11/15 11:59:59 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_convert(const char *s, int i, int count, va_list lst)
{
	if (s[i + 1] == '%')
		count = write(1, "%", 1);
	else if (s[i + 1] == 'c')
		count = ft_putchar(va_arg(lst, int));
	else if (s[i + 1] == 's')
		count = ft_putstr(va_arg(lst, char *));
	else if (s[i + 1] == 'd' || s[i + 1] == 'i')
		count = ft_putnbr(va_arg(lst, int));
	else if (s[i + 1] == 'u')
		count = ft_putnbrus(va_arg(lst, unsigned int));
	else if (s[i + 1] == 'x')
		count = ft_dectohexa(va_arg(lst, unsigned int), "0123456789abcdef");
	else if (s[i + 1] == 'X')
		count = ft_dectohexa(va_arg(lst, unsigned int), \
		"0123456789ABCDEF");
	else if (s[i + 1] == 'p')
		count = ft_pointtohexa(va_arg(lst, unsigned long long), \
		"0123456789abcdef", 1);
	else if (s[i + 1] == '\0')
		return (-1);
	else
		count = 2;
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	lst;
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (!s)
		return (-1);
	va_start(lst, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			count += ft_convert(s, i, count, lst);
			i += 2;
		}
		else
		{
			count += write(1, &s[i], 1);
			i++;
		}
	}
	va_end(lst);
	return (count);
}
