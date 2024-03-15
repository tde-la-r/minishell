/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:38:11 by amolbert          #+#    #+#             */
/*   Updated: 2024/03/15 18:21:55 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include "libft.h"

# define SPLIT_CHAR -1
# define IFS " \t\n"

# define ERR_MALLOC "minishell: malloc: "
# define ERR_PWD "minishell: pwd: "
# define ERR_EXPORT1 "minishell: export: `"
# define ERR_EXPORT2 "': not a valid identifier"

# define ENV_LOGNAME "LOGNAME"
# define ENV_USER "USER"
# define ENV_PWD "PWD"

enum e_element
{
	EL_CMD,
	EL_ARG,
	EL_PIPE,
	EL_INFILE,
	EL_HEREDOC,
	EL_OUT_T,
	EL_OUT_A,
	EL_VAR,
	EL_EXIT,
};

typedef struct s_line
{
	int				pos;
	int				type;
	char			*str;
	struct s_line	*next;
}					t_line;

typedef struct s_cmd
{
	int				fd_in;
	int				fd_out;
	char			**args;
	pid_t			pid;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_minishell
{
	int				nbenv;
	char			**env;
	char			*prompt;
	struct s_line	*line_lst;
	struct s_cmd	*cmd_lst;
	int				exit;
}					t_minishell;

char	**ft_arraydup(char **array, int nb_env);
void	free_array(char **array);
void	error_exit(char **array, char *err);

int		arg_is_well_formatted(char *to_check);
int		find_env_index(const char *to_test, char **envp);
char	*ft_getenv(const char *name, char **envp);

int		ft_pwd(void);
int		ft_env(char **envp);
int		ft_unset(char **args, char **envp, int *nb_envp);
int		ft_export(char **args, char ***envp, int *nbenv);

#endif
