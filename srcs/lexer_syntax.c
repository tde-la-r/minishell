/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:12:27 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/22 14:38:02 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dquote_error(char *line, int error, int *i)
{
	(*i)++;
	error = 1;
	while (line[*i])
	{
		if (line[*i] == '"')
		{
			error = 0;
			break ;
		}
		(*i)++;
	}
	if (error)
	{
		print_error_syn(line, '"', 0);
		return (error);
	}
	return (0);
}

int	check_squote_error(char *line, int error, int *i)
{
	(*i)++;
	error = 1;
	while (line[*i])
	{
		if (line[*i] == '\'')
		{
			error = 0;
			break ;
		}
		(*i)++;
	}
	if (error)
	{
		print_error_syn(line, '\'', 0);
		return (error);
	}
	return (0);
}

int	check_before_pipe(char *line, int *i)
{
	int		j;
	bool	arg;

	j = 0;
	arg = false;
	while (j < *i)
	{
		if (line[j] > 32 && line[j] != '|')
			arg = true;
		if (line[j] == '|')
			arg = false;
		j++;
	}
	if (!arg)
		return (1);
	return (0);
}

int	check_pipe_error(char *line, int error, int *i)
{
	error = 1;
	if (check_before_pipe(line, i))
	{
		print_error_syn(line, 'P', 0);
		return (error);
	}
	(*i)++;
	while (isifs(line[*i]))
		(*i)++;
	if (ft_isprint(line[*i]))
		error = 0;
	if (error)
	{
		print_error_syn(line, '|', 0);
		return (error);
	}
	(*i)--;
	return (0);
}

int	check_redir_error(char *line, int error, int *i, int c)
{
	int	token;

	(*i)++;
	error = 1;
	if (line[*i] == c)
		(*i)++;
	while (isifs(line[*i]))
		(*i)++;
	if (ft_isprint(line[*i]) && !ismeta(line[*i]))
		error = 0;
	if (error)
	{
		find_token(line, *i, &token);
		print_error_syn(line, c, token);
		return (error);
	}
	(*i)--;
	return (0);
}
