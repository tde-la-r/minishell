/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:47 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/14 16:50:59 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	protect_quoting(char *line, int i)
{
	char	quote_end;

	if (line[i] == '\'')
		quote_end = '\'';
	else
		quote_end = '\"';
	i++;
	while (line[i] != quote_end && line[i])
		i++;
	if (!line[i])
		return (-1);
	else
		i++;
	return (i);
}

char	*replace_ifs(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i = protect_quoting(line, i);
			if (i == -1)
				return (NULL);
			continue ;
		}
		j = 0;
		while (IFS[j])
		{
			if (line[i] == IFS[j])
				line[i] = SPLIT_CHAR;
			break ;
			j++;
		}
		i++;
	}
	return (line);
}

char	**lexicalize_line(char *line)
{
	char	**line_array;

	line = replace_ifs(line);
	if (!line)
		return (NULL);
	line_array = ft_split(line, SPLIT_CHAR);
	//if (!line_array)
		//ERR MALLOC
	//elements = assign_type_to_elements(line_array);
	//free(line_array);
	return (line_array);
}

int	main(int argc, char **argv)
{
	int	i;
	char **line_array;
	if (argc != 2)
		return (1);
	line_array = lexicalize_line(argv[1]);
	i = 0;
	while (line_array[i])
	{
		printf("%s\n", line_array[i]);
		i++;
	}
	free_array(line_array);
}
