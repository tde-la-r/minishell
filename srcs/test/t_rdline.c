/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_rdline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:39:31 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/06 17:10:33 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <readline/readline.h>

int	main()
{
	char *result;

	result = readline("> ");
	while (result)
	{
		printf("%s\n", result);
		free(result);
		result = readline("> ");
	}
	return (0);
}
