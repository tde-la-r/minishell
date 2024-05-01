/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:21:36 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/06 00:45:58 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static bool	print_argument(va_list *list, const char **arg, int *count)
{
	(*arg)++;
	if (**arg == 'i' || **arg == 'd' || **arg == 'c')
		print_integer_ptf(STDOUT_FILENO, list, **arg, count);
	else if (**arg == 'u' || **arg == 'x' || **arg == 'X')
		print_u_int_ptf(STDOUT_FILENO, list, **arg, count);
	else if (**arg == 'p')
		print_pointer_ptf(STDOUT_FILENO, list, count);
	else if (**arg == 's')
		print_string_ptf(STDOUT_FILENO, list, count);
	else if (**arg == '%')
	{
		write(STDOUT_FILENO, "%", 1);
		(*count)++;
	}
	else if (**arg)
	{
		write(STDOUT_FILENO, "%", 1);
		write(STDOUT_FILENO, *arg, 1);
		*count += 2;
	}
	else
		return (false);
	return (true);
}

static int	process_chars(va_list *list, const char *to_print, int count)
{
	while (*to_print)
	{
		if (*to_print != '%')
		{
			write(STDOUT_FILENO, to_print, 1);
			count++;
		}
		else
		{
			if (!print_argument(list, &to_print, &count))
				return (-1);
		}
		to_print++;
	}
	return (count);
}

int	ft_printf(const char *to_print, ...)
{
	va_list	list;
	int		count;

	if (!to_print)
		return (-1);
	count = 0;
	va_start(list, to_print);
	count = process_chars(&list, to_print, count);
	va_end(list);
	return (count);
}
