/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:00:35 by amolbert          #+#    #+#             */
/*   Updated: 2024/03/15 15:58:41 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(char **envp)
{
	int		index;
	char	*tmp;
	char	*old_pwd;

	index = 0;
	tmp = NULL;
	old_pwd = ft_getenv("PWD", envp);
	tmp = ft_strjoin("OLDPWD=", old_pwd);
	if (!tmp)
	{
		perror(ERR_MALLOC);
		exit (EXIT_FAILURE);
	}
	index = find_env_index("OLDPWD", envp);
	if (index == -1)
	{
		free(tmp);
		return ;
	}
	free(envp[index]);
	envp[index] = tmp;
}

static void	update_pwd(char **envp)
{
	int		index;
	char	*tmp;
	char	*pwd;

	index = 0;
	tmp = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putendl_fd("Cannot get current working directory path.\n", 2);
		exit (EXIT_FAILURE);
	}
	tmp = ft_strjoin("PWD=", pwd);
	if (!tmp)
	{
		perror(ERR_MALLOC);
		free(pwd);
		exit (EXIT_FAILURE);
	}
	index = find_env_index("PWD", envp);
	if (index == -1)
	{
		free(pwd);
		free(tmp);
		return ;
	}
	free(envp[index]);
	envp[index] = tmp;
}

static void	exec_cd(char **args, char **envp)
{
	if (chdir(args[1]) == -1)
	{
		perror("bash: cd: ");
		exit (EXIT_FAILURE);
	}
	update_oldpwd(envp);
	update_pwd(envp);
}

static void	exec_cd_home(char **envp)
{
	char	*home;

	home = ft_getenv("HOME", envp);
	if (!home)
	{
		ft_putendl_fd("bash: cd: HOME not set", 2);
		exit (EXIT_FAILURE);
	}
	if (chdir(home))
	{
		perror("bash: cd: ");
		exit (EXIT_FAILURE);
	}
	update_oldpwd(envp);
	update_pwd(envp);
}

int	ft_cd(char **args, char **envp)
{
	int		i;

	i = 1;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("bash: cd: too many arguments", 2);
		return (1);
	}
	if (i == 1)
		exec_cd_home(envp);
	else
		exec_cd(args, envp);
	//exit (EXIT_SUCCESS);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		nb_envp;
	char	**env_minishell;

	(void)argc;
	nb_envp = 0;
	while (envp[nb_envp])
		nb_envp++;
	env_minishell = ft_arraydup(envp, nb_envp);
	//ft_env(env_minishell);
	//printf("\n\n");
	//printf("%s", ft_getenv("PWD", env_minishell));
	ft_cd(argv, env_minishell);
	//printf("%s", ft_getenv("PWD", env_minishell));
	ft_env(env_minishell);
	free_array(env_minishell);
}
