/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:20:51 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/30 14:21:11 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_signal_message(int signal, bool *print, t_cmd *index)
{
	if (signal == SIGQUIT && !index->next)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		*print = false;
	}
	else if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		*print = false;
	}
}
