/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:56:08 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/23 15:55:19 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_var_operator(char **new_envp, char *dup_var, int nbenv, int j)
{
	int	i;

	i = 0;
	while (dup_var[i] && dup_var[i] != '+')
		i++;
	delete_char(dup_var, i);
	new_envp[nbenv + j] = dup_var;
}

static int	set_new_variable(char **new_envp, char *var, int nbenv, \
int *new_var_set)
{
	int			index;
	char		*dup_var;
	char		operator;

	if (!new_envp)
		return (EXIT_FAILURE);
	operator = check_operator(var);
	dup_var = ft_strdup(var);
	if (!dup_var)
		return (EXIT_FAILURE);
	index = find_env_index(var, new_envp, operator);
	if (index > -1)
	{
		if (modify_var(new_envp, dup_var, index, operator))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (operator == '=' || operator == '\0')
		new_envp[nbenv + *new_var_set] = dup_var;
	else
		add_var_operator(new_envp, dup_var, nbenv, *new_var_set);
	(*new_var_set)++;
	return (EXIT_SUCCESS);
}

static char	**create_new_envp(char **args, char **envp, int nbenv, int new_vars)
{
	int		i;
	int		new_var_set;
	char	**new_envp;

	new_envp = ft_arraydup(envp, nbenv + new_vars);
	if (!new_envp)
		return (NULL);
	i = 1;
	new_var_set = 0;
	while (args[i])
	{
		if (arg_is_well_formatted(args[i]) > 0)
			if (set_new_variable(new_envp, args[i], nbenv, &new_var_set))
				free_array(&new_envp);
		i++;
	}
	return (new_envp);
}

static int	parse_args(char **args, char **envp, int *nbenv)
{
	int	i;
	int	format;
	int	ret;
	int	operator;

	ret = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		format = arg_is_well_formatted(args[i]);
		operator = check_operator(args[i]);
		if (format < 0)
		{
			print_error_msg(args[i]);
			ret = EXIT_FAILURE;
		}
		if (find_env_index(args[i], envp, operator) == -1 && format > 0)
			if (is_not_prev_arg(args, i))
				(*nbenv)++;
		i++;
	}
	return (ret);
}

int	ft_export(int fd, char **args, t_minishell *data)
{
	int		ret;
	int		new_vars;
	char	**new_envp;

	new_envp = NULL;
	if (!args[1])
	{
		if (export_no_arg(data->env, new_envp, data->nbenv, fd))
			error_exit(data, NULL, NULL, "malloc");
		return (0);
	}
	new_vars = 0;
	ret = parse_args(args, data->env, &new_vars);
	new_envp = create_new_envp(args, data->env, data->nbenv, new_vars);
	if (!new_envp)
		error_exit(data, NULL, NULL, "malloc");
	free_array(&data->env);
	data->env = new_envp;
	data->nbenv += new_vars;
	return (ret);
}
