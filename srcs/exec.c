/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:05:32 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/29 14:01:03 by tde-la-r         ###   ########.fr       */
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

static bool	exec_builtin(t_cmd *cmd, int fd_out, bool child, t_minishell *data)
{
	if (!cmd->args[0] || cmd->fd_in == -1 || fd_out == -1)
		return (false);
	if (!ft_is_builtin(cmd->args[0]))
		return (false);
	if (!ft_strncmp(cmd->args[0], "cd", BUILTIN_CMP_LEN))
		data->exit = ft_cd(fd_out, cmd->args, data);
	else if (!ft_strncmp(cmd->args[0], "env", BUILTIN_CMP_LEN))
		data->exit = ft_env(data, fd_out, cmd->args, data->env);
	else if (!ft_strncmp(cmd->args[0], "unset", BUILTIN_CMP_LEN))
		data->exit = ft_unset(cmd->args, data->env, &data->nbenv);
	else if (!ft_strncmp(cmd->args[0], "export", BUILTIN_CMP_LEN))
		data->exit = ft_export(fd_out, cmd->args, data);
	else if (!ft_strncmp(cmd->args[0], "pwd", BUILTIN_CMP_LEN))
		data->exit = ft_pwd(fd_out);
	else if (!ft_strncmp(cmd->args[0], "exit", BUILTIN_CMP_LEN))
		data->exit = ft_exit(cmd->args, data, child);
	else if (!ft_strncmp(cmd->args[0], "echo", BUILTIN_CMP_LEN))
		data->exit = ft_echo(fd_out, cmd->args);
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
	if (exec_builtin(to_exec, STDOUT_FILENO, B_CHILD, data))
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
	int	signal;

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
				signal = WTERMSIG(status);
				if (signal == SIGQUIT && !index->next)
					printf("Quit (core dumped)\n");
				if (signal == SIGINT)
					printf("\n");
				data->exit = signal + 128;
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
		if (!exec_builtin(list, list->fd_out, B_PARENT, data))
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
