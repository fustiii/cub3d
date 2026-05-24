#include "../inc/cub3d.h"

static int	init_mlx_assets(t_game *data)
{
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	data->mlx.minimap = mlx_new_image(data->mlx.mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!data->mlx.img || !data->mlx.minimap)
	{
		data->error_msg = "Error: Failed to create MLX image buffers";
		return (ERROR);
	}
	if (mlx_image_to_window(data->mlx.mlx, data->mlx.img, 0, 0) < 0
		|| mlx_image_to_window(data->mlx.mlx, data->mlx.minimap, 0, 0) < 0)
		return (ERROR);
	if (load_textures(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	start_game_graphics(t_game *data)
{
	data->mlx.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!data->mlx.mlx)
	{
		data->error_msg = "Error: Failed to initialize MLX library";
		exit_error(data);
	}
	if (init_mlx_assets(data) == ERROR)
	{
		exit_mlx(&data->mlx);
		exit_error(data);
	}
	mlx_loop_hook(data->mlx.mlx, &render_frame, data);
	mlx_key_hook(data->mlx.mlx, &hook_key, data);
	mlx_loop(data->mlx.mlx);
	exit_mlx(&data->mlx);
}