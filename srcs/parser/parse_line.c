/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:54:58 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/22 15:13:54 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_syntax_error(char *line)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (line[i])
	{
		if (line[i] == '"')
			error = check_dquote_error(line, error, &i);
		else if (line[i] == '\'')
			error = check_squote_error(line, error, &i);
		else if (line[i] == '|')
			error = check_pipe_error(line, error, &i);
		else if (line[i] == '>')
			error = check_redir_error(line, error, &i, '>');
		else if (line[i] == '<')
			error = check_redir_error(line, error, &i, '<');
		if (error)
			return (ECODE_SYNTAX);
		i++;
	}
	return (ECODE_SUCCESS);
}

static void	init_lst_lexer(char *line, t_minishell *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!isifs(line[i]) && !ismeta(line[i]))
			create_node_arg(data, line, &i);
		else if (line[i] == '|')
			create_node_pipe(data, line, &i, '|');
		else if (line[i] == '>' && line[i + 1] != '>')
			create_node_redir(data, line, &i, 'T');
		else if (line[i] == '>' && line[i + 1] == '>')
			create_node_redir(data, line, &i, 'A');
		else if (line[i] == '<' && line[i + 1] != '<')
			create_node_redir(data, line, &i, 'I');
		else if (line[i] == '<' && line[i + 1] == '<' )
			create_node_redir(data, line, &i, 'H');
		else
			i++;
	}
	free(line);
}

bool	parse_line(char *line, t_minishell *data)
{
	int	ret;

	if (!*line)
	{
		free(line);
		return (B_FAILURE);
	}
	add_history(line);
	ret = check_syntax_error(line);
	if (ret)
	{
		data->exit = ret;
		return (B_FAILURE);
	}
	init_lst_lexer(line, data);
	expand_variables(data);
	split_args_variables(data);
	del_quote_arg_element(data->line_lst);
	return (B_SUCCESS);
}
