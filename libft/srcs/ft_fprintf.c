/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:21:36 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/01 17:55:47 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_fprintf(int fd, const char *to_print, ...)
{
	va_list	list;
	int		count;

	if (!to_print)
		return (-1);
	count = 0;
	va_start(list, to_print);
	count = process_chars_ptf(fd, &list, to_print, count);
	va_end(list);
	return (count);
}
