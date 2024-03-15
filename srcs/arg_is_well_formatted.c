/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_well_formatted.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:01:52 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/15 15:02:16 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_is_well_formatted(char *to_check)
{
	int	i;

	i = 0;
	if (ft_isdigit(to_check[i]))
		return (-1);
	while (to_check[i] != '=' && to_check[i])
	{
		if (!ft_isalnum(to_check[i]) && to_check[i] != '_')
			return (-1);
		i++;
	}
	if (!i)
		return (-1);
	if (!to_check[i])
		return (0);
	return (1);
}

