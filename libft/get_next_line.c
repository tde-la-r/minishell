/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:07:36 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/01/11 13:22:55 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	

static char	*read_line(int fd, char *buffer, char *save)
{
	int		nb_char;
	char	*tmp;

	while (!ft_strchr(buffer, '\n'))
	{
		nb_char = read(fd, buffer, BUFFER_SIZE);
		if (nb_char == -1)
			return (NULL);
		if (!nb_char)
			break ;
		buffer[nb_char] = 0;
		tmp = save;
		save = ft_strjoin(tmp, buffer);
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
	return (save);
}

static char	*extract(char *line)
{
	size_t	count;
	char	*save;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (NULL);
	save = ft_substr(line, count + 1, ft_strlen(line) - count);
	line[count + 1] = '\0';
	if (!save)
		return (NULL);
	if (!*save)
	{
		free(save);
		save = NULL;
	}
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*save[1024];

	if (fd > 1024 || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	*buffer = 0;
	if (!buffer)
		return (NULL);
	line = read_line(fd, buffer, save[fd]);
	free(buffer);
	if (!line)
		return (NULL);
	if (!*line)
		return (NULL);
	save[fd] = extract(line);
	return (line);
}
