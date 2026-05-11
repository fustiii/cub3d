#include "../inc/cub3d.h"

void hook_render(void* param)
{
    t_game   *data = (t_game*)param;
    
    (void)data;
    // 1. Dibujar Suelo y Techo (Background)
    // 2. Ejecutar Raycasting
    // 3. Pintar en cub->screen usando mlx_put_pixel
}

void hook_key(mlx_key_data_t keydata, void* param)
{
    t_game  *data = (t_game*)param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(data->mlx.mlx);
}

void handle_input(t_cub *cub)
{
    if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
        // player_move_forward(cub);
    if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
        // player_rotate_left(cub); [cite: 118, 119]
}