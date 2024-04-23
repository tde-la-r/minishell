/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:05:32 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/23 19:47:30 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execve_error_exit(t_minishell *data, char *cmd)
{
	char		*err_msg;
	int			err_code;
	struct stat	statbuf;

	err_code = errno;
	err_msg = strerror(err_code);
	if (err_code == ENOENT && !ft_strchr(cmd, '/'))
		err_msg = ERR_CMD_NOT_FOUND;
	if (err_code == EACCES)
	{
		if (stat(cmd, &statbuf) == -1)
			perror("minishell: stat");
		if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
			err_msg = ERR_ISDIR;
	}
	if (*cmd)
		ft_dprintf(STDERR_FILENO, "%s%s: %s\n", ERR_MSG_START, cmd, err_msg);
	else
		ft_dprintf(STDERR_FILENO, "%s'': %s\n", ERR_MSG_START, err_msg);
	free_memory(data, NULL, NULL, B_NO_DEL);
	if (err_code == ENOENT)
		exit (ECODE_CMD_NOT_FOUND);
	if (err_code == EACCES)
		exit(ECODE_ACCESSEXECVE);
	exit (EXIT_FAILURE);
}

static bool	exec_builtin(char **args, t_cmd *cmd, bool child, t_minishell *data)
{
	if (!args[0] || cmd->fd_in == -1 || cmd->fd_out == -1)
		return (false);
	if (!ft_is_builtin(args[0]))
		return (false);
	if (!ft_strncmp(args[0], "cd", BUILTIN_CMP_LEN))
		data->exit = ft_cd(cmd->fd_out, args, data);
	else if (!ft_strncmp(args[0], "env", BUILTIN_CMP_LEN))
		data->exit = ft_env(data, cmd->fd_out, args, data->env);
	else if (!ft_strncmp(args[0], "unset", BUILTIN_CMP_LEN) && !child)
		data->exit = ft_unset(args, data->env, &data->nbenv);
	else if (!ft_strncmp(args[0], "export", BUILTIN_CMP_LEN))
		data->exit = ft_export(cmd->fd_out, args, data);
	else if (!ft_strncmp(args[0], "pwd", BUILTIN_CMP_LEN))
		data->exit = ft_pwd(cmd->fd_out);
	else if (!ft_strncmp(args[0], "exit", BUILTIN_CMP_LEN) && !child)
		data->exit = ft_exit(args, data);
	else if (!ft_strncmp(args[0], "echo", BUILTIN_CMP_LEN))
		data->exit = ft_echo(cmd->fd_out, args);
	return (true);
}

static void	exec_cmd_in_child(t_cmd *to_exec, t_minishell *data)
{
	int		tmp;
	bool	exec;

	to_exec->pid = fork();
	if (to_exec->pid == -1)
		child_error_exit(data, "minishell: fork");
	if (to_exec->pid)
		return ;
	if (dup2(to_exec->fd_in, STDIN_FILENO) == -1)
		child_error_exit(data, "dup2");
	if (dup2(to_exec->fd_out, STDOUT_FILENO) == -1)
		child_error_exit(data, "dup2");
	close_fds(data->cmd_lst);
	if (exec_builtin(to_exec->args, to_exec, B_CHILD, data))
	{
		tmp = data->exit;
		free_memory(data, NULL, NULL, B_NO_DEL);
		exit(tmp);
	}
	to_exec->args[0] = format_cmd(data, to_exec->args[0], &exec);
	sigaction(SIGQUIT, &data->standard, NULL);
	sigaction(SIGINT, &data->standard, NULL);
	if (exec)
		execve(to_exec->args[0], to_exec->args, data->env);
	execve_error_exit(data, to_exec->args[0]);
}

static void	wait_childs(t_cmd *index, t_minishell *data)
{
	int	status;

	while (index)
	{
		if (index->pid)
		{
			if (waitpid(index->pid, &status, 0) == -1)
				error_exit(data, NULL, NULL, "waitpid");
			if (WIFEXITED(status))
				data->exit = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					printf("Quit (core dumped)");
				printf("\n");
				data->exit = WTERMSIG(status) + 128;
			}
		}
		index = index->next;
	}
}

void	exec_cmds(t_minishell *data)
{
	t_cmd	*list;
	t_cmd	*index;

	list = data->cmd_lst;
	if (ft_cmdsize(list) == 1)
	{
		if (!exec_builtin(list->args, list, B_PARENT, data))
			exec_cmd_in_child(list, data);
	}
	else
	{
		index = list;
		while (index)
		{
			exec_cmd_in_child(index, data);
			index = index->next;
		}
	}
	close_fds(list);
	wait_childs(list, data);
}
