/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:55:09 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/24 13:22:33 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	increment_shlvl(t_minishell *data, char **env)
{
	char	*content;
	char	*tmp;
	int		lvl;
	int		index;

	index = find_env_index("SHLVL", env, '=');
	if (index == -1)
		return ;
	content = ft_strchr(env[index], '=') + 1;
	lvl = ft_atoi(content) + 1;
	content = ft_itoa(lvl);
	if (!content)
		error_exit(data, NULL, NULL, "malloc");
	tmp = ft_strjoin("SHLVL=", content);
	free(content);
	if (!tmp)
		error_exit(data, NULL, NULL, "malloc");
	free(env[index]);
	env[index] = tmp;
}

static void	init_env(t_minishell *data, char **envp)
{
	if (!envp)
		data->env = ft_calloc(sizeof(char *), 1);
	else
	{
		while (envp[data->nbenv])
			data->nbenv++;
		data->env = ft_arraydup(envp, data->nbenv);
	}
	if (!data->env)
		error_exit(data, NULL, NULL, "malloc");
	increment_shlvl(data, data->env);
}

static void	interactive_new_line(int signal)
{
	g_signal = signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

t_minishell	*init_data(char **envp)
{
	t_minishell	*data;

	data = ft_calloc(sizeof(*data), 1);
	if (!data)
		error_exit(NULL, NULL, NULL, "malloc");
	init_env(data, envp);
	data->heredocs = ft_calloc(sizeof(char *), 1);
	if (!data->heredocs)
		error_exit(data, NULL, NULL, "malloc");
	data->ignore.sa_handler = SIG_IGN;
	data->standard.sa_handler = SIG_DFL;
	data->new_line.sa_handler = &interactive_new_line;
	find_path_envp(data);
	return (data);
}
