/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:16:20 by gfuster           #+#    #+#             */
/*   Updated: 2026/05/27 11:16:30 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	assign_player_data(t_game *data, int y, int x)
{
	char	pos;

	pos = data->map.map[y][x];
	if (pos == 'N' || pos == 'S' || pos == 'E' || pos == 'W')
	{
		if (data->map.player_y != -1)
			return (ERROR);
		data->map.player_y = y;
		if (data->map.player_x != -1)
			return (ERROR);
		data->map.player_x = x;
		if (data->map.player_dir != -1)
			return (ERROR);
		data->map.player_dir = pos;
	}
	return (SUCCESS);
}

int	allowed_character(char pos)
{
	int	is_allowed;

	is_allowed = 0;
	if (pos == '0')
		is_allowed = 1;
	if (pos == '1')
		is_allowed = 1;
	if (pos == ' ')
		is_allowed = 1;
	if (pos == 'N')
		is_allowed = 1;
	if (pos == 'S')
		is_allowed = 1;
	if (pos == 'E')
		is_allowed = 1;
	if (pos == 'W')
		is_allowed = 1;
	return (is_allowed);
}

static int	calculate_max_cols(char **map)
{
	int	max_cols;
	int	i;
	int	j;

	max_cols = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			j++;
		}
		i++;
		if (j > max_cols)
			max_cols = j;
	}
	return (max_cols);
}

static char	*line_to_map(char *src, int max_cols)
{
	char	*dst;
	int		len;

	dst = malloc(sizeof(char) * (max_cols + 1));
	if (!dst)
		return (NULL);
	len = ft_strlen(src);
	ft_strlcpy(dst, src, max_cols + 1);
	while (len < max_cols)
	{
		dst[len] = ' ';
		len++;
	}
	dst[len] = '\0';
	return (dst);
}

int	extract_map(t_game *data, char **map)
{
	int	i;

	i = 0;
	data->map.cols = calculate_max_cols(map);
	while (map[i] && !is_empty(map[i]))
		i++;
	data->map.rows = i;
	data->map.map = malloc(sizeof(char *) * (i + 1));
	if (!data->map.map)
		return (ERROR);
	i = -1;
	while (map[++i] && !is_empty(map[i]))
	{
		trim_newline(map[i]);
		data->map.map[i] = line_to_map(map[i], data->map.cols);
		if (!data->map.map[i])
			return (ERROR);
	}
	data->map.map[i] = NULL;
	if (map[i] != NULL)
	{
		data->error_msg = "Error: Empty lines or extra content after map";
		return (ERROR);
	}
	return (SUCCESS);
}
