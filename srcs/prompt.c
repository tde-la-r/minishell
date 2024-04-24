/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:40:52 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/24 12:43:47 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_home(char *pwd, t_minishell *data)
{
	char	*home;
	char	*result;
	size_t	len;

	home = ft_getenv("HOME", data->env);
	if (!home)
		return (pwd);
	len = ft_strlen(home);
	if (!ft_strncmp(home, pwd, len) && (!pwd[len] || pwd[len] == '/'))
	{
		result = ft_strjoin("~", pwd + len);
		free(pwd);
		if (!result)
			error_exit(data, NULL, NULL, "malloc");
	}
	else
		return (pwd);
	return (result);
}

static char	*set_working_dir(t_minishell *data)
{
	char	*pwd;

	pwd = ft_getenv("PWD", data->env);
	if (pwd)
	{
		pwd = ft_strdup(pwd);
		if (!pwd)
			error_exit(data, NULL, NULL, "malloc");
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			perror(ERR_INIT_GETCWD);
			return (NULL);
		}
	}
	pwd = replace_home(pwd, data);
	return (pwd);
}

static char	*append_sep_chars(char *to_format, t_minishell *data)
{
	size_t	len;
	char	*pwd;

	if (!to_format)
		return (NULL);
	len = ft_strlen(to_format);
	pwd = ft_calloc(sizeof(char), len + 4);
	if (!pwd)
		error_exit(data, NULL, to_format, "malloc");
	pwd[0] = ':';
	ft_strlcat(pwd, to_format, len + 2);
	free(to_format);
	ft_strlcat(pwd, "$ ", len + 4);
	return (pwd);
}

static char	*set_color(t_minishell *data, char *prompt)
{
	char		*tmp;
	static int	color = 0;

	tmp = check_color(data, prompt, &color);
	color++;
	if (color > 5)
		color = 0;
	prompt = ft_strjoin(tmp, RESET);
	free(tmp);
	if (!prompt)
		error_exit(data, NULL, NULL, "malloc");
	return (prompt);
}

char	*set_prompt(t_minishell *data)
{
	char	*pwd;
	char	*sep_chars;
	char	*logname;
	char	*prompt;

	pwd = set_working_dir(data);
	sep_chars = append_sep_chars(pwd, data);
	logname = ft_getenv("LOGNAME", data->env);
	if (!logname)
		logname = ft_getenv("USER", data->env);
	prompt = ft_strjoin(logname, sep_chars);
	if (sep_chars)
		free(sep_chars);
	if (!prompt)
		error_exit(data, NULL, NULL, "malloc");
	prompt = set_color(data, prompt);
	return (prompt);
}
