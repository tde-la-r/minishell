/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:38:11 by amolbert          #+#    #+#             */
/*   Updated: 2024/04/19 11:29:07 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*==================================includes=================================*/

# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/*==================================defines==================================*/

# define SPLIT_CHAR -1
# define BACKSLASH_QUOTE -2
# define IFS " \t\n"

# define TMP_DIR "/tmp/"
# define TMP_DIR_LEN 5
# define ERR_HERE_DOC "minishell: warning: here-document \
delimited by end-of-file"
# define URANDOM_FILE "/dev/urandom"
# define ERR_URANDOM_OPEN "minishell: can't open /dev/urandom"
# define ERR_URANDOM_READ "minishell: can't read /dev/urandom"
# define PROMPT_HEREDOC "> "

# define B_SUCCESS false
# define B_FAILURE true
# define B_DEL true
# define B_NO_DEL false

# define HEREDOC_SIGNALED -2

# define ERR_MSG_START "minishell: "
# define ERR_CMD_NOT_FOUND "command not found"
# define ERR_ISDIR "Is a directory"
# define ERR_MALLOC "minishell: malloc"
# define ERR_STAT "minishell: stat"
# define ERR_PIPE "minishell: pipe"
# define ERR_FORK "minishell: fork"
# define ERR_DUP "minishell: dup2"
# define ERR_CD_ARGS "minishell: cd: too many arguments"
# define ERR_CD_OLDPWD "minishell: cd: OLDPWD not set"
# define ERR_WAIT "minishell: wait"
# define ERR_WAITPID "minishell: waitpid"
# define ERR_OPEN "minishell: open"
# define ERR_PWD "minishell: pwd"
# define ERR_AMB_REDIR "minishell: ambiguous redirect"
# define ERR_EXPORT1 "minishell: export: `"
# define ERR_EXPORT2 "': not a valid identifier"
# define ERR_EXIT "minishell: exit: too many arguments"
# define ERR_UNLINK "minishell: unlink"
# define ERR_GETCWD "minishell: getcwd"
# define ERR_INIT_GETCWD "minishell-init: error retrieving current directory: \
	getcwd: cannot access parent directories"

# define ECODE_SUCCESS 0
# define ECODE_CMD_NOT_FOUND 127
# define ECODE_SYNTAX 2
# define ECODE_ACCESSEXECVE 126
# define BUILTIN_CMP_LEN 7
# define ECODE_SIGINT 130

# define ERR_SYN_REDIR "minishell: syntax error near unexpected token" 
# define ERR_SYN_SQ "minishell: unexpected EOF while looking for matching `\''" 
# define ERR_SYN_DQ "minishell: unexpected EOF while looking for matching `\"'" 
# define ERR_SYN_EOF "minishell: syntax error: unexpected end of file" 
# define ERR_SYN_PIPE "minishell: syntax error near unexpected token `|'" 

# define ENV_LOGNAME "LOGNAME"
# define ENV_USER "USER"
# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"
# define ENV_HOME "HOME"
# define ENV_PATH "PATH"

# define B_CD "cd"
# define B_ENV "env"
# define B_PWD "pwd"
# define B_EXPORT "export"
# define B_UNSET "unset"
# define B_ECHO "echo"
# define B_EXIT "exit"

extern int	g_signal;

typedef enum e_type
{
	EL_ARG,
	EL_PIPE,
	EL_INFILE,
	EL_HEREDOC,
	EL_OUT_T,
	EL_OUT_A,
}			t_type;

/*=================================structures================================*/

typedef struct s_line
{
	int				index;
	int				type;
	char			*str;
	struct s_line	*prev;
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
	int					exit;
	int					nbenv;
	char				**env;
	char				**paths;
	char				**heredocs;
	char				*prompt;
	char				*line;
	struct s_line		*line_lst;
	struct s_cmd		*cmd_lst;
	struct sigaction	new_line;
	struct sigaction	ignore;
	struct sigaction	standard;
}					t_minishell;

/*=================================utils_2.c=================================*/
char	**ft_arraydup(char **array, int nbstr);
char	*ft_getenv(const char *name, char **envp);
int		find_env_index(const char *to_test, char **envp, int plus);

/*=================================prompt.c==================================*/
char	*set_prompt(t_minishell *data);

/*=================================cmd_lst.c=================================*/
void	init_lst_cmd(t_minishell *data);
int		find_nb_args(t_line *line_lst);

/*===============================parse_line.c================================*/
bool	parse_line(char *line, t_minishell *data);

/*===================================exec.c==================================*/
void	exec_cmds(t_minishell *data);

/*=================================builtins==================================*/
int		ft_pwd(int fd);
int		ft_env(int fd, char **args, char **envp);
int		ft_unset(char **args, char **envp, int *nb_envp);
int		ft_cd(int fd, char **args, t_minishell *data);
int		ft_exit(char **args, t_minishell *to_free);
int		ft_echo(int fd, char **args);

/*===============================export_utils.c==============================*/
int		add_first_quote(char **envp, char **new_envp, int i);
int		add_second_quote(char **envp, char **new_envp, int i);
int		modify_var(char **new_envp, char *dup_var, int index, int operator);
void	print_error_msg(char *arg);
char	*select_content(char *var);

/*=============================export_no_args.c==============================*/
int		export_no_arg(char **envp, char **new_envp, int nbenv, int fd);

/*=================================export.c==================================*/
int		ft_export(int fd, char **args, t_minishell *data);

/*===============================create_node.c===============================*/
void	create_node_quote(t_minishell *data, char *line, int *i, int c);
void	create_node_arg(t_minishell *data, char *line, int *i);
void	create_node_redirections(t_minishell *data, char *line, int *i, int c);
void	create_node_pipe(t_minishell *data, char *line, int *i, int c);

/*============================create_node_utils.c============================*/
int		check_type(int c);
t_line	*init_node(char *line, int i, int len, int c);

/*===============================lexer_utils.c===============================*/
int		ft_isifs(int c);
int		ft_ismeta(int c);
void	print_error_syn(char *line, int c);

/*==============================lexer_syntax.c===============================*/
int		check_dquote_error(char *line, int error, int *i);
int		check_squote_error(char *line, int error, int *i);
int		check_pipe_error(char *line, int error, int *i);
int		check_redir_error(char *line, int error, int *i, int token);

/*==============================cmd_lst_utils.c==============================*/
void	ft_cmddelone(t_cmd *lst);
void	ft_cmdclear(t_cmd **lst);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
int		ft_cmdsize(t_cmd *list);
t_line	*ft_lnnew(int index, int type, char *str, t_line *prev);

/*==============================ln_lst_utils.c===============================*/
void	ft_lnadd_back(t_line **ln, t_line *new);
void	ft_lnclear(t_line **lst);
void	ft_lndelone(t_line *lst);

/*==================================utils.c==================================*/
bool	isifs(int c);
bool	isredirection(t_line element);
bool	isquote(int c);
void	free_array(char ***array);
int		skip_quote(char quote, char *str, int i);

/*===============================error_utils.c===============================*/
void	error_exit(t_minishell *data, t_cmd *node, char *str, char *err);
void	free_heap_memory(t_minishell *data, t_cmd *node, char *str, bool del);
void	close_fds(t_cmd *lst);
void	del_heredocs(char **heredocs);
void	child_error_exit(t_minishell *data, char *err_msg);

/*===============================split_args.c================================*/
void	split_args_variables(t_minishell *data);
char	**split_ifs(char *str);

/*=========================expand_variables_utils.c==========================*/
char	*count_var_quotes(char *var);
char	*insert_backslash_quotes(char *var);
int		find_name_len(char *var);

/*=============================expand_variables.c============================*/
void	expand_variables(t_minishell *data);
char	*substitute_variable(char *line, int *i, t_minishell data);

/*===============================format_cmd.c================================*/
bool	ft_is_builtin(char *arg);
char	*format_cmd(t_minishell *data, char *arg, bool *exec);

/*==========================arg_is_well_formated.c===========================*/
int		arg_is_well_formatted(char *to_check);
int		check_operator(char *to_check);

/*================================del_quote.c================================*/
void	delete_char(char *arg, int pos);
void	find_quote(char *arg);
void	del_quote_arg_element(t_line *lst);

/*================================init_fds.c=================================*/
t_cmd	*create_next_node(t_minishell *data, t_cmd **new, t_line *pipe);
t_cmd	*ft_cmdnew(int cmd_in, int nb_args);
t_cmd	*fds_redir(t_minishell *data, t_cmd *new, t_line *redir);

/*================================here_docs.c================================*/
int		create_here_doc(char *limiter, t_minishell *data, t_cmd *new);

/*=============================here_docs_utils.c=============================*/
void	check_signal(int signal);
void	set_signal(bool *expand, char *limiter, int *limiter_len);
int		receive_signal(t_minishell *data, t_cmd *new);
void	delete_all_char(char *str, char to_delete);

#endif
