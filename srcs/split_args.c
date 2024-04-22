/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:47 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/22 16:07:03 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_ifs(char *str)
{
	int		i;
	char	**array;

	i = 0;
	while (str[i])
	{
		i = skip_quote('\'', str, i);
		i = skip_quote('"', str, i);
		if (isifs(str[i]))
			str[i] = SPLIT_CHAR;
		i++;
	}
	array = ft_split(str, SPLIT_CHAR);
	return (array);
}

static t_line	*clear_element(t_line *element, char **array, t_minishell *data)
{
	t_line	*tmp;

	if (!element->prev)
		data->line_lst = element->next;
	else
		element->prev->next = element->next;
	if (element->next)
		element->next->prev = element->prev;
	tmp = element->next;
	ft_lndelone(element);
	free(array);
	return (tmp);
}

static t_line	*add_args(t_line *ind, char **str, t_line *next, t_minishell *f)
{
	t_line	*new;
	int		i;
	int		pos;

	pos = ind->index;
	i = 1;
	while (str[i])
	{
		new = ft_lnnew(pos + i, EL_ARG, str[i], ind);
		if (!new)
		{
			while (str[i])
			{
				free(str[i]);
				i++;
			}
			free(str);
			ind->next = next;
			error_exit(f, NULL, NULL, "malloc");
		}
		ind->next = new;
		ind = ind->next;
		i++;
	}
	return (ind);
}

static t_line	*rearrange_arg(t_line *element, char **array, t_minishell *data)
{
	t_line	*last_added;
	t_line	*next_element;
	int		new_pos;

	if (!*array)
	{
		next_element = clear_element(element, array, data);
		return (next_element);
	}
	free(element->str);
	element->str = array[0];
	next_element = element->next;
	last_added = add_args(element, array, next_element, data);
	last_added->next = next_element;
	if (next_element)
		next_element->prev = last_added;
	new_pos = last_added->index;
	while (next_element)
	{
		new_pos++;
		next_element->index = new_pos;
		next_element = next_element->next;
	}
	free(array);
	return (element->next);
}

void	split_args_variables(t_minishell *data)
{
	t_line	*index;
	char	**array;

	index = data->line_lst;
	while (index)
	{
		if (index->type == EL_ARG)
		{
			array = split_ifs(index->str);
			if (!array)
				error_exit(data, NULL, NULL, "malloc");
			index = rearrange_arg(index, array, data);
			continue ;
		}
		index = index->next;
	}
}
