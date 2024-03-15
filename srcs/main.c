/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:25:52 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/15 18:46:26 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	init_data(char **envp)
{
	t_minishell	init;

	init.nbenv = 0;
	if (!envp)
	{
		init.env = ft_calloc(sizeof(char *), 1);
		if (!init.env)
			error_exit(NULL, ERR_MALLOC);
	}
	else
	{
		while (envp[init.nbenv])
			init.nbenv++;
		init.env = ft_arraydup(envp, init.nbenv);
	}
	init.prompt = set_prompt(envp);
	init.exit = 0;
	init.line_lst = NULL;
	init.cmd_lst = NULL;
	return (init);
}

void	ft_exit(t_minishell to_free)
{
	free(to_free.prompt);
	ft_lnclear(&to_free.line);
	ft_cmdclear(&to_free.cmd);
	free_array(to_free.env);
	printf("exit\n");
	exit (to_free.exit);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	char		*line;

	(void) argc;
	(void) argv;
	data = init_data(envp);
	line = readline(data.prompt);
	while (line)
	{
		add_history(line);
		free(line);
		line = readline(data.prompt);
	}
	ft_exit(data);
}
