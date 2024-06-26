/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:23:00 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/22 15:40:49 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_builtin(char *arg)
{
	if (!ft_strncmp(arg, "echo", 5) || !ft_strncmp(arg, "exit", 6))
		return (true);
	if (!ft_strncmp(arg, "cd", 3) || !ft_strncmp(arg, "pwd", 4))
		return (true);
	if (!ft_strncmp(arg, "export", 7) || !ft_strncmp(arg, "unset", 6))
		return (true);
	if (!ft_strncmp(arg, "env", 4))
		return (true);
	return (false);
}

static void	switch_exec(bool *exec)
{
	*exec = false;
	errno = ENOENT;
}

static char	*check_access(t_minishell *data, char *tmp, bool *exec)
{
	int		i;
	int		len;
	char	*cmd;

	i = 0;
	len = ft_strlen(tmp);
	while (data->paths && data->paths[i])
	{
		cmd = ft_strjoin(data->paths[i], tmp);
		if (!cmd)
			return (NULL);
		if (!access(cmd, X_OK))
			return (cmd);
		free(cmd);
		i++;
	}
	cmd = ft_substr(tmp, 1, len - 1);
	switch_exec(exec);
	return (cmd);
}

char	*format_cmd(t_minishell *data, char *arg, bool *exec)
{
	char	*path;
	char	*tmp;

	if (!arg)
	{
		free_memory(data, NULL, NULL, B_NO_DEL);
		exit(EXIT_SUCCESS);
	}
	if (!*arg)
	{
		switch_exec(exec);
		return (arg);
	}
	*exec = true;
	if (ft_strchr(arg, '/'))
		return (arg);
	tmp = ft_strjoin("/", arg);
	if (!tmp)
		child_error_exit(data, "malloc");
	path = check_access(data, tmp, exec);
	free(tmp);
	if (!path)
		child_error_exit(data, "malloc");
	free(arg);
	return (path);
}
