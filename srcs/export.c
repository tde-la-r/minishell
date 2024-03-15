/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:56:08 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/15 15:23:32 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_msg(char *arg)
{
	char	*tmp;
	char	*to_print;

	tmp = ft_strjoin(ERR_EXPORT1, arg);
	if (!tmp)
		error_exit(NULL, ERR_MALLOC);
	to_print = ft_strjoin(tmp, ERR_EXPORT2);
	free(tmp);
	if (!to_print)
		error_exit(NULL, ERR_MALLOC);
	ft_putendl_fd(to_print, 2);
	free(to_print);
}

static void	set_new_variable(char **new_envp, char *var, int nbenv)
{
	static int	i = 1;
	int			index;
	char		*dup_var;

	dup_var = ft_strdup(var);
	if (!dup_var)
		error_exit(new_envp, ERR_MALLOC);
	index = find_env_index(var, new_envp);
	if (index > -1)
	{
		free(new_envp[index]);
		new_envp[index] = dup_var;
	}
	else
	{
		new_envp[nbenv - i] = dup_var;
		i++;
	}
}

static char	**create_new_envp(char **args, char **envp, int nbenv)
{
	int		i;
	char	**new_envp;

	new_envp = ft_calloc(sizeof(char *) , nbenv + 1);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = envp[i];
		i++;
	}
	i = 1;
	while (args[i])
	{
		if (arg_is_well_formatted(args[i]) > 0)
			set_new_variable(new_envp, args[i], nbenv);
		i++;
	}
	return (new_envp);
}

static int	parse_args(char **args, char **envp, int *nbenv)
{
	int		i;
	int		format;
	int		ret;

	ret = 0;
	i = 1;
	while (args[i])
	{
		format = arg_is_well_formatted(args[i]);
		if (format < 0)
		{
			print_error_msg(args[i]);
			ret = 1;
		}
		if (find_env_index(args[i], envp) == -1 && format > 0)
			(*nbenv)++;
		i++;
	}
	return (ret);
}

int	ft_export(char **args, char ***envp, int *nbenv)
{
	int		ret;
	char	**new_envp;

	if (!args[1])
	{
		ft_env(*envp);
		return (0);
	}
	ret = parse_args(args, *envp, nbenv);
	new_envp = create_new_envp(args, *envp, *nbenv);
	free(*envp);
	*envp = new_envp;
	return (ret);
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
	ft_env(env_minishell);
	ft_export(argv, &env_minishell, &nb_envp);
	printf("\n\n");
	ft_env(env_minishell);
	free_array(env_minishell);
}
