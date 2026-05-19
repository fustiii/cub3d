#include "../inc/cub3d.h"

int    load_textures(t_game *data)
{
    int i;

    data->mlx.texture[0] = mlx_load_png(data->no_path);
    data->mlx.texture[1] = mlx_load_png(data->so_path);
    data->mlx.texture[2] = mlx_load_png(data->we_path);
    data->mlx.texture[3] = mlx_load_png(data->ea_path);
    i = 0;
    while (i < 4)
    {
        if (!data->mlx.texture[i])
        {
            data->error_msg = "Error: Textures failed to load";
            return (ERROR);
        }
        i++;
    }
    return (SUCCESS);
}