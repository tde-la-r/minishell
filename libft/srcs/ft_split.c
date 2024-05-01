/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:37:17 by tde-la-r          #+#    #+#             */
/*   Updated: 2023/12/31 17:18:02 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_strings(const char *s, char c)
{
	int	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static void	free_and_exit(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
}

static char	*make_substring(const char *s, char c, unsigned int *index)
{
	unsigned int	length;
	unsigned int	i;
	char			*substring;

	while (s[*index] == c)
		(*index)++;
	length = 0;
	while (s[length + *index] != c && s[length + *index])
		length++;
	substring = malloc(sizeof(char) * (length + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < length)
	{
		substring[i] = s[*index + i];
		i++;
	}
	substring[i] = 0;
	*index += length;
	return (substring);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	unsigned int	index;
	unsigned int	i;
	unsigned int	strings_number;

	if (!s)
		return (NULL);
	strings_number = count_strings(s, c);
	result = malloc((strings_number + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	index = 0;
	while (i < strings_number)
	{
		result[i] = make_substring(s, c, &index);
		if (!result[i])
		{
			free_and_exit(result, i);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
