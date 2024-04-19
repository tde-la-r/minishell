/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:21:36 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/06 00:48:36 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static bool	print_argument(int fd, va_list *list, const char **arg, int *count)
{
	(*arg)++;
	if (**arg == 'i' || **arg == 'd' || **arg == 'c')
		print_integer_ptf(fd, list, **arg, count);
	else if (**arg == 'u' || **arg == 'x' || **arg == 'X')
		print_u_int_ptf(fd, list, **arg, count);
	else if (**arg == 'p')
		print_pointer_ptf(fd, list, count);
	else if (**arg == 's')
		print_string_ptf(fd, list, count);
	else if (**arg == '%')
	{
		write(fd, "%", 1);
		(*count)++;
	}
	else if (**arg)
	{
		write(fd, "%", 1);
		write(fd, *arg, 1);
		*count += 2;
	}
	else
		return (false);
	return (true);
}

static int	process_chars(int fd, va_list *list, const char *arg, int count)
{
	while (*arg)
	{
		if (*arg != '%')
		{
			write(fd, arg, 1);
			count++;
		}
		else
		{
			if (!print_argument(fd, list, &arg, &count))
				return (-1);
		}
		arg++;
	}
	return (count);
}

int	ft_dprintf(int fd, const char *to_print, ...)
{
	va_list	list;
	int		count;

	if (!to_print)
		return (-1);
	count = 0;
	va_start(list, to_print);
	count = process_chars(fd, &list, to_print, count);
	va_end(list);
	return (count);
}
