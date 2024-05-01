/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:44:48 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/17 20:59:14 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_char(char *arg, int pos)
{
	int	i;
	int	end;

	i = 0;
	end = ft_strlen(arg) - 1;
	while (i <= end)
	{
		if (i == pos)
		{
			while (i <= end)
			{
				arg[i] = arg[i + 1];
				i++;
			}
			arg[i] = '\0';
			break ;
		}
		i++;
	}
}

static void	apply_del_quote(char *arg, int *i)
{
	delete_char(arg, *i);
	while (arg[*i] != '\"')
	{
		if (arg[*i] == BACKSLASH_QUOTE)
			delete_char(arg, *i);
		(*i)++;
	}
	delete_char(arg, *i);
	(*i)--;
}

void	find_quote(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == BACKSLASH_QUOTE)
			delete_char(arg, i);
		else if (arg[i] == '\"')
			apply_del_quote(arg, &i);
		else if (arg[i] == '\'')
		{
			delete_char(arg, i);
			while (arg[i] != '\'')
				i++;
			delete_char(arg, i);
			i--;
		}
		i++;
	}
}

void	del_quote_arg_element(t_line *lst)
{
	while (lst)
	{
		if (lst->type == EL_ARG)
			find_quote(lst->str);
		lst = lst->next;
	}
}
