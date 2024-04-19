/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_well_formatted.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:01:52 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/17 20:58:15 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_operator(char *to_check)
{
	int	i;

	i = 0;
	if (!to_check)
		return ('=');
	while (to_check[i])
	{
		if (to_check[i] == '+')
			return ('+');
		i++;
	}
	return ('=');
}

static int	check_arg(char *to_check, int *i, int plus)
{
	if (plus == '+')
	{
		while (to_check[*i] && (to_check[*i] != '+' && to_check[*i + 1] != '='))
		{
			if (!ft_isalnum(to_check[*i]) && to_check[*i] != '_')
				return (-1);
			(*i)++;
		}
	}
	else
	{
		while (to_check[*i] && to_check[*i] != '=')
		{
			if (!ft_isalnum(to_check[*i]) && to_check[*i] != '_')
				return (-1);
			(*i)++;
		}
	}
	return (0);
}

int	arg_is_well_formatted(char *to_check)
{
	int	i;
	int	plus;

	i = 0;
	if (ft_isdigit(to_check[i]))
		return (-1);
	plus = check_operator(to_check);
	if (check_arg(to_check, &i, plus) == -1)
		return (-1);
	if (!i)
		return (-1);
	if (!to_check[i])
		return (0);
	return (1);
}
