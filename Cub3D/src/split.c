/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:00:42 by gfuster           #+#    #+#             */
/*   Updated: 2025/10/31 20:04:25 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*copy_word(char const *start, int len)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		word_index;
	int		start;
	int		len;
	char	**result;

	result = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	word_index = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		start = i;
		while (str[i] && str[i] != c)
			i++;
		len = i - start;
		if (len > 0)
			result[word_index++] = copy_word(&str[start], len);
	}
	result[word_index] = NULL;
	return (result);
}
