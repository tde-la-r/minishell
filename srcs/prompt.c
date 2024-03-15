/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:40:52 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/12 14:59:11 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_prompt(char **envp)
{
	char	*logname;
	char	*pwd;
	char	*cwd;

	logname = ft_getenv(ENV_LOGNAME, envp);
	if (!logname)
		logname = ft_getenv(ENV_USER, envp);
	cwd = NULL;
	pwd = ft_getenv(ENV_PWD, envp);
	if (!pwd)
		cwd = getcwd(NULL, 0);
}
