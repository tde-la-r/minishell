/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:00:35 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/16 21:49:49 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(char **envp, t_minishell *data)
{
	int		index;
	char	*tmp;
	char	*old_pwd;

	old_pwd = ft_getenv("PWD", envp);
	if (!old_pwd)
		return ;
	tmp = ft_strjoin("OLDPWD=", old_pwd);
	if (!tmp)
		error_exit(data, NULL, NULL, ERR_MALLOC);
	index = find_env_index("OLDPWD", envp, '=');
	if (index == -1)
	{
		free(tmp);
		return ;
	}
	free(envp[index]);
	envp[index] = tmp;
}

static void	update_pwd(char **envp, t_minishell *data)
{
	int		index;
	char	*tmp;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror(ERR_GETCWD);
		return ;
	}
	tmp = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!tmp)
		error_exit(data, NULL, NULL, ERR_MALLOC);
	index = find_env_index(ENV_PWD, envp, '=');
	if (index == -1)
	{
		free(tmp);
		return ;
	}
	free(envp[index]);
	envp[index] = tmp;
}

static char	*get_target(char *to_find, char **envp, int fd)
{
	char	*var;

	var = ft_getenv(to_find, envp);
	if (!var)
		ft_dprintf(STDERR_FILENO, "%scd: %s not set\n", ERR_MSG_START, to_find);
	if (fd != -1)
		ft_putendl_fd(var, fd);
	return (var);
}

int	ft_cd(int fd, char **args, t_minishell *data)
{
	char	*target;
	char	*err;

	if (args[1] && args[2])
	{
		ft_putendl_fd(ERR_CD_ARGS, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	target = args[1];
	if (!args[1])
		target = get_target(ENV_HOME, data->env, -1);
	else if (!ft_strncmp("-", args[1], 2))
		target = get_target(ENV_OLDPWD, data->env, fd);
	if (!target)
		return (EXIT_FAILURE);
	if (chdir(target) == -1)
	{
		err = strerror(errno);
		ft_dprintf(STDERR_FILENO, "%scd: %s: %s\n", ERR_MSG_START, target, err);
		return (EXIT_FAILURE);
	}
	update_oldpwd(data->env, data);
	update_pwd(data->env, data);
	return (EXIT_SUCCESS);
}
