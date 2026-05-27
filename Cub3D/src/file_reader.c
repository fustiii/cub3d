/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:09:42 by gfuster           #+#    #+#             */
/*   Updated: 2026/05/27 11:09:45 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	count_lines(int fd)
{
	size_t	lines;
	char	buf[4096];
	int		i;
	char	last_char;
	int		bytes_read;

	last_char = '\n';
	lines = 0;
	bytes_read = read(fd, buf, sizeof(buf));
	while (bytes_read > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			if (buf[i] == '\n')
				lines++;
			i++;
		}
		last_char = buf[bytes_read - 1];
		bytes_read = read(fd, buf, sizeof(buf));
	}
	if (last_char != '\n' && bytes_read != -1)
		lines++;
	return (lines);
}

int	open_file(t_game *data, const char *pathname)
{
	int	fd;

	fd = open(pathname, O_RDWR);
	if (fd < 0)
	{
		data->error_msg = strerror(errno);
		return (ERROR);
	}
	return (fd);
}

char	**file_to_array(t_game *data, char *file)
{
	char	**file_content;
	int		i;
	int		fd;

	fd = open_file(data, file);
	if (fd == ERROR)
		return (NULL);
	file_content = malloc(sizeof(char *) * (count_lines(fd) + 1));
	close(fd);
	if (!file_content)
		return (NULL);
	fd = open_file(data, file);
	i = 0;
	file_content[i] = get_next_line(fd);
	while (file_content[i] != NULL)
	{
		i++;
		file_content[i] = get_next_line(fd);
	}
	close(fd);
	return (file_content);
}
