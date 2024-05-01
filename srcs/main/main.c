/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:25:52 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/01 13:33:39 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_signal = 0;

void	find_path_envp(t_minishell *data)
{
	char	*var;

	var = ft_getenv("PATH", data->env);
	if (!var)
		return ;
	data->paths = ft_split(var, ':');
	if (!data->paths)
		error_exit(data, NULL, NULL, "malloc");
}

static void	set_up_new_line(t_minishell *data)
{
	ft_lnclear(&data->line_lst);
	ft_cmdclear(&data->cmd_lst);
	del_heredocs(data->heredocs);
	free_array(&data->heredocs);
	data->heredocs = ft_calloc(sizeof(char *), 1);
	if (!data->heredocs)
		error_exit(data, NULL, NULL, "malloc");
	free_array(&data->paths);
	find_path_envp(data);
}

static char	*call_readline(t_minishell *data)
{
	char	*line;

	data->prompt = set_prompt(data);
	data->line_count++;
	sigaction(SIGINT, &data->new_line, NULL);
	line = readline(data->prompt);
	sigaction(SIGINT, &data->ignore, NULL);
	if (g_signal)
	{
		data->exit = g_signal + 128;
		g_signal = 0;
	}
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*data;
	char		*line;

	(void) argc;
	(void) argv;
	data = init_data(envp);
	sigaction(SIGQUIT, &data->ignore, NULL);
	line = call_readline(data);
	while (line)
	{
		if (!parse_line(line, data))
		{
			init_lst_cmd(data);
			exec_cmds(data);
			set_up_new_line(data);
		}
		free(data->prompt);
		line = call_readline(data);
	}
	ft_exit(NULL, data, B_PARENT);
}
