/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:50:13 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/19 18:15:28 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isifs(int c)
{
	if (c == ' ' || c == '	' || c == '\n')
		return (1);
	else
		return (0);
}

int	ft_ismeta(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

void	find_token(char *line, int i, int *token)
{
	if (!line[i])
		*token = 0;
	else if (line[i] == '|')
		*token = EL_PIPE;
	else if (line[i] == '>' && line[i + 1] != '>')
		*token = EL_OUT_T;
	else if (line[i] == '<' && line[i + 1] != '<')
		*token = EL_INFILE;
	else if (line[i] == '>' && line[i + 1] == '>')
		*token = EL_HEREDOC;
	else if (line[i] == '<' && line[i + 1] == '<')
		*token = EL_OUT_A;
}

static void	print_err_redir(int token)
{
	if (token == 0)
		ft_dprintf(STDERR_FILENO, "%s `%s'\n", ERR_SYN_REDIR, "newline");
	if (token == EL_PIPE)
		ft_dprintf(STDERR_FILENO, "%s `%s'\n", ERR_SYN_REDIR, "|");
	if (token == EL_OUT_T)
		ft_dprintf(STDERR_FILENO, "%s `%s'\n", ERR_SYN_REDIR, ">");
	if (token == EL_OUT_A)
		ft_dprintf(STDERR_FILENO, "%s `%s'\n", ERR_SYN_REDIR, "<<");
	if (token == EL_INFILE)
		ft_dprintf(STDERR_FILENO, "%s `%s'\n", ERR_SYN_REDIR, "<");
	if (token == EL_HEREDOC)
		ft_dprintf(STDERR_FILENO, "%s `%s'\n", ERR_SYN_REDIR, ">>");
}

void	print_error_syn(char *line, int c, int token)
{
	if (c == '<' || c == '>')
		print_err_redir(token);
	if (c == '\"')
		ft_dprintf(STDERR_FILENO, "%s\n%s\n", ERR_SYN_DQ, ERR_SYN_EOF);
	if (c == '\'')
		ft_dprintf(STDERR_FILENO, "%s\n%s\n", ERR_SYN_SQ, ERR_SYN_EOF);
	if (c == '|')
		ft_putendl_fd(ERR_SYN_EOF, STDERR_FILENO);
	if (c == 'P')
		ft_putendl_fd(ERR_SYN_PIPE, STDERR_FILENO);
	free(line);
}
