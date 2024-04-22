/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:52:09 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/22 17:24:57 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_var_to_sub(char *line, int i, int *len, t_minishell data)
{
	char	*name;
	char	*var;

	*len = find_name_len(line + i);
	name = ft_substr(line, i, *len);
	if (!name)
		return (NULL);
	var = ft_getenv(name, data.env);
	if (var)
		var = insert_backslash_quotes(var);
	if (*name == '?')
		var = ft_itoa(data.exit);
	if (*name == '~')
		var = ft_strdup("$~");
	*len += i;
	if (isquote(line[i]) || line[i] == '\\' || isifs(line[i]) || !line[i])
	{
		*len = i;
		var = ft_strdup("$");
	}
	free(name);
	return (var);
}

char	*substitute_variable(char *line, int *i, t_minishell data)
{
	char	*var;
	char	*line_piece;
	char	*beginning;
	char	*result;
	int		name_len;

	var = find_var_to_sub(line, *i + 1, &name_len, data);
	line_piece = ft_substr(line, 0, *i);
	beginning = ft_strjoin(line_piece, var);
	if (line_piece)
		free(line_piece);
	line_piece = line + name_len;
	result = ft_strjoin(beginning, line_piece);
	if (beginning)
		free(beginning);
	if (!errno)
		free(line);
	*i += ft_strlen(var) - 1;
	if (var)
		free(var);
	return (result);
}

static char	*find_expand_case(char *str, t_minishell *data)
{
	int		i;
	bool	in_dquote;

	in_dquote = false;
	i = 0;
	while (str[i])
	{
		if (!in_dquote)
			i = skip_quote('\'', str, i);
		if (str[i] == '"')
			in_dquote = !in_dquote;
		if (str[i] == '$' && isquote(str[i + 1]) && !in_dquote)
			str[i] = SPLIT_CHAR;
		else if (str[i] == '$')
		{
			errno = 0;
			str = substitute_variable(str, &i, *data);
			if (errno)
				error_exit(data, NULL, str, "malloc");
		}
		i++;
	}
	return (str);
}

void	expand_variables(t_minishell *data)
{
	t_line	*index;

	index = data->line_lst;
	while (index)
	{
		while (index && index->type == EL_HEREDOC)
			index = index->next;
		if (!index)
			break ;
		index->str = find_expand_case(index->str, data);
		index = index->next;
	}
}
