/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:51:43 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/04/19 18:05:51 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*gen_file(t_minishell *data, t_cmd *new, int *fd_file, int len)
{
	char				*path;
	char				*buffer;
	int					fd_urandom;
	ssize_t				ret;

	buffer = ft_calloc(sizeof(char), len + 1);
	if (!buffer)
		error_exit(data, new, NULL, ERR_MALLOC);
	fd_urandom = open(URANDOM_FILE, O_RDONLY);
	if (fd_urandom == -1)
		error_exit(data, new, buffer, ERR_URANDOM_OPEN);
	ret = read(fd_urandom, buffer, len);
	close(fd_urandom);
	if (ret == -1)
		error_exit(data, new, buffer, ERR_URANDOM_READ);
	buffer[len] = '\0';
	path = ft_strjoin(TMP_DIR, buffer);
	free(buffer);
	if (!path)
		error_exit(data, new, NULL, ERR_MALLOC);
	*fd_file = open(path, O_WRONLY | O_CREAT | O_EXCL, 0644);
	return (path);
}

static void	add_heredoc_to_data(char *to_add, t_minishell *data, \
t_cmd *new, int fd)
{
	int		count;
	char	**new_array;

	count = 0;
	while (data->heredocs[count])
		count++;
	new_array = ft_arraydup(data->heredocs, count + 1);
	if (!new_array)
	{
		close(fd);
		error_exit(data, new, to_add, ERR_MALLOC);
	}
	new_array[count] = to_add;
	free_array(&data->heredocs);
	data->heredocs = new_array;
}

static void	write_input(int fd, bool expand, t_minishell *data, t_cmd *new)
{
	int		i;

	if (expand)
	{
		i = 0;
		while (data->line[i])
		{
			if (data->line[i] == '$')
			{
				errno = 0;
				data->line = substitute_variable(data->line, &i, *data);
				if (errno)
				{
					close(fd);
					error_exit(data, new, NULL, ERR_MALLOC);
				}
				delete_all_char(data->line, BACKSLASH_QUOTE);
			}
			i++;
		}
	}
	ft_putendl_fd(data->line, fd);
	free(data->line);
	data->line = readline(PROMPT_HEREDOC);
}

static void	get_input(int fd, char *limiter, t_minishell *data, t_cmd *new)
{
	bool				expand;
	pid_t				pid;
	int					limiter_len;

	pid = fork();
	if (pid == -1)
	{
		close(fd);
		error_exit(data, new, NULL, ERR_FORK);
	}
	if (pid)
		return ;
	limiter_len = 0;
	set_signal(&expand, limiter, &limiter_len);
	data->line = readline(PROMPT_HEREDOC);
	while (!g_signal && (ft_strncmp(data->line, limiter, limiter_len + 1)))
		write_input(fd, expand, data, new);
	close (fd);
	if (!data->line)
		ft_dprintf(STDERR_FILENO, "%s%s%d%s%s')\n", \
				ERR_MSG_START, ERR_HD1, data->line_count, ERR_HD2, limiter);
	free_memory(data, new, NULL, B_NO_DEL);
	if (g_signal)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int	create_here_doc(char *limiter, t_minishell *data, t_cmd *new)
{
	char	*name;
	int		fd;
	int		name_len;

	name_len = 1;
	name = gen_file(data, new, &fd, name_len);
	while (fd == -1 && errno == EEXIST)
	{
		free(name);
		name_len++;
		name = gen_file(data, new, &fd, name_len);
	}
	if (fd == -1)
		error_exit(data, new, name, ERR_OPEN);
	add_heredoc_to_data(name, data, new, fd);
	get_input(fd, limiter, data, new);
	close(fd);
	if (receive_signal(data, new))
		return (HEREDOC_SIGNALED);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		error_exit(data, new, NULL, ERR_OPEN);
	return (fd);
}
