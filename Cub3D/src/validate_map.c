#include "../inc/cub3d.h"

static int	is_player_character(char pos)
{
	return (pos == 'N' || pos == 'S' || pos == 'E' || pos == 'W');
}

static int	validate_cell(t_game *data, int y, int x)
{
	char	cell;

	cell = data->map.map[y][x];
	if (!allowed_character(cell))
	{
		data->error_msg = "Error: Invalid character in map";
		return (ERROR);
	}
	if (is_player_character(cell))
	{
		if (assign_player_data(data, y, x) == ERROR)
		{
			data->error_msg = "Error: Map has more than one player";
			return (ERROR);
		}
	}
	return (SUCCESS);
}

static int	check_map_characters(t_game *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map.map[y])
	{
		x = 0;
		while (data->map.map[y][x])
		{
			if (validate_cell(data, y, x) == ERROR)
				return (ERROR);
			x++;
		}
		y++;
	}
	if (data->map.player_y == -1)
	{
		data->error_msg = "Error: No player position found";
		return (ERROR);
	}
	return (SUCCESS);
}

int	validate_map(t_game *data)
{
	if (check_map_characters(data) == ERROR)
		return (ERROR);
	if (flood_fill(data) == ERROR)
	{
		data->error_msg = "Error: Map is not enclosed by walls";
		return (ERROR);
	}
	return (SUCCESS);
}