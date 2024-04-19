/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:40:52 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/16 21:53:43 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_home(char *pwd, t_minishell *data)
{
	char	*home;
	char	*result;
	size_t	len;

	home = ft_getenv(ENV_HOME, data->env);
	if (!home)
		return (pwd);
	len = ft_strlen(home);
	if (!ft_strncmp(home, pwd, len) && (!pwd[len] || pwd[len] == '/'))
	{
		result = ft_strjoin("~", pwd + len);
		free(pwd);
		if (!result)
			error_exit(data, NULL, NULL, ERR_MALLOC);
	}
	else
		return (pwd);
	return (result);
}

static char	*set_working_dir(t_minishell *data)
{
	char	*pwd;

	pwd = ft_getenv(ENV_PWD, data->env);
	if (pwd)
	{
		pwd = ft_strdup(pwd);
		if (!pwd)
			error_exit(data, NULL, NULL, ERR_MALLOC);
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

	len = ft_strlen(to_format);
	pwd = ft_calloc(sizeof(char), len + 4);
	if (!pwd)
		error_exit(data, NULL, to_format, ERR_MALLOC);
	pwd[0] = ':';
	ft_strlcat(pwd, to_format, len + 2);
	free(to_format);
	ft_strlcat(pwd, "$ ", len + 4);
	return (pwd);
}

char	*set_prompt(t_minishell *data)
{
	char	*pwd;
	char	*sep_chars;
	char	*logname;
	char	*prompt;

	pwd = set_working_dir(data);
	sep_chars = append_sep_chars(pwd, data);
	logname = ft_getenv(ENV_LOGNAME, data->env);
	if (!logname)
		logname = ft_getenv(ENV_USER, data->env);
	prompt = ft_strjoin(logname, sep_chars);
	free(sep_chars);
	if (!prompt)
		error_exit(data, NULL, NULL, ERR_MALLOC);
	return (prompt);
}
