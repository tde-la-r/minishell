/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:16:23 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/01 17:56:23 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>

int		process_chars_ptf(int fd, va_list *list, const char *arg, int count);
void	print_pointer_ptf(int fd, va_list *list, int *count);
void	print_u_int_ptf(int fd, va_list *list, const char arg, int *count);
void	print_integer_ptf(int fd, va_list *list, const char arg, int *count);
void	print_string_ptf(int fd, va_list *list, int *count);
size_t	ft_strlen(const char *s);

#endif
