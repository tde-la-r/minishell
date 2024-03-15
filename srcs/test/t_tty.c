/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tty.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:34:51 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/05 12:22:16 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main()
{
	printf("%s\n", ttyname(STDIN_FILENO));
	printf("%s\n", ttyname(STDOUT_FILENO));
	printf("%s\n", ttyname(STDERR_FILENO));
}
