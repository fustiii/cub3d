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

int	extract_map(t_game *data, char **map)
{
	int	i;

	i = 0;
	trim_newline(map[0]);
	data->map.cols = ft_strlen(map[i]);
	while (map[i] && !is_empty(map[i]))
		i++;
	data->map.rows = i;
	data->map.map = malloc(sizeof(char *) * (i + 1));
	if (!data->map.map)
		return (ERROR);
	i = 0;
	while (map[i] && !is_empty(map[i]))
	{
		trim_newline(map[i]);
		data->map.map[i] = ft_strdup(map[i]);
		i++;
	}
	data->map.map[i] = NULL;
	return (SUCCESS);
}
