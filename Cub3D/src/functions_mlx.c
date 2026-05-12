#include "../inc/cub3d.h"

void    load_textures(t_game *data)
{
    data.mlx.texture[0] = mlx_load_xpm42(data.no_path);
    data.mlx.texture[1] = mlx_load_xpm42(data.so_path);
    data.mlx.texture[2] = mlx_load_xpm42(data.we_path);
    data.mlx.texture[3] = mlx_load_xpm42(data.ea_path);
    if (!data.mlx.texture[0] || !data.mlx.texture[1] ||
            !data.mlx.texture[2] || !data.mlx.texture[3])
        exit_error(&data);
}

void hook_render(void *param)
{
    t_game   *data = (t_game*)param;
    
    (void)data;
    // 1. Dibujar Suelo y Techo (Background)
    // 2. Ejecutar Raycasting
    // 3. Pintar en cub->screen usando mlx_put_pixel
}

void hook_key(mlx_key_data_t keydata, void *param)
{
    t_game  *data = (t_game*)param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(data->mlx.mlx);
}

void handle_input(t_game *data)
{
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_W))
    {
        // player_move_forward(cub);
    }
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_LEFT))
    {
        // player_rotate_left(cub); [cite: 118, 119]
    }
}