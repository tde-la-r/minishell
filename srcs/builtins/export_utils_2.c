/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:01:52 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/01 15:00:03 by tde-la-r         ###   ########.fr       */
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
	int	len_cur_arg;
	int	len_prev_arg;

	j = 1;
	len_cur_arg = 0;
	while (args[index][len_cur_arg] && \
			args[index][len_cur_arg] != '=' && args[index][len_cur_arg] != '+')
		len_cur_arg++;
	while (j < index)
	{
		len_prev_arg = 0;
		while (args[j][len_prev_arg] \
				&& args[j][len_prev_arg] != '=' && args[j][len_prev_arg] != '+')
			len_prev_arg++;
		len = ft_superior(len_prev_arg, len_cur_arg);
		if (!ft_strncmp(args[index], args[j], len))
			return (false);
		j++;
	}
	return (true);
}
