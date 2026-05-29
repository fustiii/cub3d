/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:10:44 by gfuster           #+#    #+#             */
/*   Updated: 2026/05/27 11:10:45 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	fill(char **map, int y, int x, int height)
{
	if (y < 0 || y >= height || x < 0 || map[y][x] == '\0' || map[y][x] == ' ')
		return (ERROR);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (SUCCESS);
	map[y][x] = 'V';
	if (fill(map, y + 1, x, height) == ERROR
		|| fill(map, y - 1, x, height) == ERROR
		|| fill(map, y, x + 1, height) == ERROR
		|| fill(map, y, x - 1, height) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	flood_fill(t_game *data)
{
	char	**tmp;
	int		y;
	int		x;

	tmp = copy_map(data->map.map, data->map.rows);
	if (!tmp)
		return (ERROR);
	y = 0;
	while (tmp[y])
	{
		x = 0;
		while (tmp[y][x])
		{
			if (is_walkable(tmp[y][x]))
			{
				if (fill(tmp, y, x, data->map.rows) == ERROR)
					return (free_array(tmp), ERROR);
			}
			x++;
		}
		y++;
	}
	free_array(tmp);
	return (SUCCESS);
}
