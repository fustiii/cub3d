/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:49:23 by gfuster           #+#    #+#             */
/*   Updated: 2025/07/02 15:08:39 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i])
			res[i] = s1[i];
	while (s2[j])
		res[i++] = s2[j++];
	res[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (res);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		new_s = (char *)malloc(1);
		if (!new_s)
			return (NULL);
		new_s[0] = '\0';
		return (new_s);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	new_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < len)
		new_s[i++] = s[start++];
	new_s[i] = '\0';
	return (new_s);
}
