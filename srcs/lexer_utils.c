/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:50:13 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/17 16:51:28 by tde-la-r         ###   ########.fr       */
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

void	print_error_syn(char *line, int c)
{
	if (c == '<' || c == '>')
		ft_putendl_fd(ERR_SYN_REDIR, STDERR_FILENO);
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
