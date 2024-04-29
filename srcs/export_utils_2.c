/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:01:52 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/29 00:58:20 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_operator(char *to_check)
{
	int	i;

	i = 0;
	if (!to_check)
		return ('=');
	while (to_check[i] && to_check[i] != '=')
	{
		if (to_check[i] == '+')
			return ('+');
		i++;
	}
	if (to_check[i] == '=')
		return ('=');
	return ('\0');
}

bool	arg_is_well_formatted(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[0]))
		return (false);
	while (ft_isalnum(arg[i]) || arg[i] == '_')
		i++;
	if (i && (!arg[i] || arg[i] == '=' || (arg[i] == '+' && arg[i + 1] == '=')))
		return (true);
	return (false);
}

bool	is_not_prev_arg(char **args, int index)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (args[index][len] && \
			args[index][len] != '=' && args[index][len] != '+')
		len++;
	while (j < index)
	{
		if (!ft_strncmp(args[index], args[j], len))
			return (false);
		j++;
	}
	return (true);
}
