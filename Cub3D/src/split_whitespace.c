/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:17:49 by gfuster           #+#    #+#             */
/*   Updated: 2026/05/27 11:17:53 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	count_words(char const *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (is_space(str[i]))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && !is_space(str[i]))
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

char	**ft_split_whitespace(char const *str)
{
	int		i;
	int		word_index;
	int		start;
	int		len;
	char	**result;

	result = malloc(sizeof(char *) * (count_words(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	word_index = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		start = i;
		while (str[i] && !is_space(str[i]))
			i++;
		len = i - start;
		if (len > 0)
			result[word_index++] = copy_word(&str[start], len);
	}
	result[word_index] = NULL;
	return (result);
}
