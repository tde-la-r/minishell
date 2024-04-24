/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:54:45 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/24 16:05:11 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	chech_size_arg(char *arg)
{
	int				i;
	int				sign;
	unsigned long	s;

	i = 0;
	sign = 0;
	s = 0;
	while (arg[i] == ' ' || arg[i] == '\t' || arg[i] == '\v' || \
	arg[i] == '\f' || arg[i] == '\r' || arg[i] == '\n')
		i++;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign = 1;
		i++;
	}
	while (arg[i])
	{
		if (s * 10 + (arg[i] - '0') > (unsigned long)LONG_MAX + sign)
			return (false);
		s = s * 10 + (arg[i] - '0');
		i++;
	}
	return (true);
}

static unsigned char	char_to_uchar(char *s)
{
	int		d;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	d = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\v' || \
	s[i] == '\f' || s[i] == '\r' || s[i] == '\n')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		d = 10 * d + (s[i] - '0');
		i++;
	}
	return (sign * d);
}

static unsigned char	args_check(char **args)
{
	int	i;
	int	j;

	if (!args || !args[1])
		return (0);
	i = 1;
	j = 0;
	while (args[i][j] == ' ')
		j++;
	if (args[i][j] == '-' || args[i][j] == '+')
		j++;
	while (isdigit(args[i][j]))
		j++;
	if (args[i][j])
		return (2);
	if (!chech_size_arg(args[1]))
		return (2);
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd(ERR_EXIT, STDERR_FILENO);
		return (1);
	}
	return (0);
}

char	*error_msg(char *arg)
{
	char	*tmp;
	char	*err;

	tmp = ft_strjoin("minishell: exit: ", arg);
	if (!tmp)
		return (NULL);
	err = ft_strjoin(tmp, ": numeric argument required");
	free(tmp);
	if (!err)
		perror("minishell: malloc");
	return (err);
}

int	ft_exit(char **args, t_minishell *data, bool child)
{
	int		ret;
	char	*err;

	if (!child)
		ft_putendl_fd("exit", STDERR_FILENO);
	ret = args_check(args);
	if (ret == 2)
	{
		err = error_msg(args[1]);
		ft_putendl_fd(err, STDERR_FILENO);
		if (err)
			free(err);
		free_memory(data, NULL, NULL, B_DEL);
		exit (ret);
	}
	if (ret == 1)
		return (ret);
	if (!args || !args[1])
		ret = data->exit;
	else
		ret = char_to_uchar(args[1]);
	free_memory(data, NULL, NULL, B_DEL);
	exit (ret);
}
