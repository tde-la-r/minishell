/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:25:52 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/19 17:51:00 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static void	setup_new_line(t_minishell *data)
{
	ft_lnclear(&data->line_lst);
	ft_cmdclear(&data->cmd_lst);
	free_array(&data->paths);
	del_heredocs(data->heredocs);
	free_array(&data->heredocs);
	data->heredocs = ft_calloc(sizeof(char *), 1);
	if (!data->heredocs)
		error_exit(data, NULL, NULL, ERR_MALLOC);
	free(data->prompt);
	data->prompt = set_prompt(data);
	find_path_envp(data);
}

void	find_path_envp(t_minishell *data)
{
	char	*var;

	var = ft_getenv(ENV_PATH, data->env);
	if (!var)
		return ;
	data->paths = ft_split(var, ':');
	if (!data->paths)
		error_exit(data, NULL, NULL, ERR_MALLOC);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell		*data;
	char			*line;

	(void) argc;
	(void) argv;
	data = init_data(envp);
	sigaction(SIGINT, &data->new_line, NULL);
	sigaction(SIGQUIT, &data->ignore, NULL);
	line = readline(data->prompt);
	sigaction(SIGINT, &data->ignore, NULL);
	while (line)
	{
		add_history(line);
		if (!parse_line(line, data))
		{
			init_lst_cmd(data);
			exec_cmds(data);
			setup_new_line(data);
		}
		data->line_count++;
		sigaction(SIGINT, &data->new_line, NULL);
		line = readline(data->prompt);
		sigaction(SIGINT, &data->ignore, NULL);
	}
	ft_exit(NULL, data);
}
