#include "../inc/cub3d.h"

static void    init_player(t_player *player)
{
	player->pos_y = 0.0;
	player->pos_x = 0.0;
	player->dir_y = 0.0;
	player->dir_x = 0.0;
	player->plane_y = 0.0;
	player->plane_x = 0.0;
}

static void    init_map(t_map *map)
{
	map->map = NULL;
	map->rows = 0;
	map->cols = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = -1;
}

static void    init_mlx(t_mlx *mlx)
{
	int i;
	
	mlx->mlx = NULL;
	mlx->img = NULL;
	mlx->minimap = NULL;
	i = 0;
	while (i < 4)
	{
		mlx->texture[i] = NULL;
		i++;
	}
}


void init_data(t_game *data)
{
	data->no_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->ea_path = NULL;
	data->floor_rgb = -1;
	data->ceil_rgb = -1;
	data->error_msg = NULL;
	init_map(&data->map);
	init_player(&data->player);
	init_mlx(&data->mlx);
}