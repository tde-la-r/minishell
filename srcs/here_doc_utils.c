/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:32:56 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/22 16:24:33 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = signal;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	set_signal(bool *expand, char *limiter, int *limiter_len)
{
	struct sigaction	act;

	*expand = true;
	if (ft_strchr(limiter, '"') || ft_strchr(limiter, '\''))
		*expand = false;
	find_quote(limiter);
	*limiter_len = ft_strlen(limiter);
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &check_signal;
	sigaction(SIGINT, &act, NULL);
}

int	receive_signal(t_minishell *data, t_cmd *new)
{
	int	status;

	sigaction(SIGINT, &data->ignore, NULL);
	if (wait(&status) == -1)
		error_exit(data, new, NULL, "wait");
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == EXIT_FAILURE)
			return (HEREDOC_SIGNALED);
	}
	return (0);
}

void	delete_all_char(char *str, char to_delete)
{
	int		i;
	char	*next;

	str = ft_strchr(str, to_delete);
	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	next = ft_strchr(str, to_delete);
	if (next)
		delete_all_char(next, to_delete);
}
