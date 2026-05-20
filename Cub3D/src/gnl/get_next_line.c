/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:36:45 by gfuster           #+#    #+#             */
/*   Updated: 2025/07/02 15:49:42 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Para open
#include <fcntl.h>
Para printf
#include <stdio.h>
*/
#include "../../inc/get_next_line.h"

char	*extract_line(char *stash)
{
	char	*line;
	int		len;
	char	*newline_pos;

	newline_pos = ft_strchr(stash, '\n');
	if (newline_pos)
		len = newline_pos - stash + 1;
	else
		len = ft_strlen(stash);
	line = ft_substr(stash, 0, len);
	return (line);
}

char	*clean_stash(char *stash)
{
	char	*rest;
	char	*restline_pos;
	size_t	len_rest;

	if (!stash)
		return (NULL);
	restline_pos = ft_strchr(stash, '\n');
	if (restline_pos)
	{
		len_rest = ft_strlen(restline_pos + 1);
		rest = ft_substr(stash, (unsigned int)(restline_pos - stash + 1),
				len_rest);
		free(stash);
		return (rest);
	}
	else
	{
		free(stash);
		return (NULL);
	}
}

int	found_newline(char *stash)
{
	int	i;

	i = 0;
	if (!stash)
		return (0);
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_and_join(int fd, char *stash)
{
	char	*buffer;
	int		chars_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	chars_read = 1;
	while (!found_newline(stash) && chars_read > 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read == -1)
		{
			free (buffer);
			free (stash);
			return (NULL);
		}
		if (chars_read == 0)
			break ;
		buffer[chars_read] = '\0';
		stash = ft_strjoin_gnl(stash, buffer);
	}
	free (buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_join(fd, stash);
	if (!stash)
		return (NULL);
	if (stash[0] == '\0')
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*res;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error abriendo el archivo");
		return (1);
	}
	while ((res = get_next_line(fd)) != NULL)
	{
		printf("Line: %s\n", res);
		free (res);
	}
	close(fd);
	return (0);
}
*/
