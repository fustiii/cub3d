#include "../inc/cub3d.h"

void    load_textures(t_game *data)
{
    data->mlx.texture[0] = mlx_load_xpm42(data->no_path);
    data->mlx.texture[1] = mlx_load_xpm42(data->so_path);
    data->mlx.texture[2] = mlx_load_xpm42(data->we_path);
    data->mlx.texture[3] = mlx_load_xpm42(data->ea_path);
    if (!data->mlx.texture[0] || !data->mlx.texture[1] ||
            !data->mlx.texture[2] || !data->mlx.texture[3])
        exit(1);
        //exit_error(&data);
}

void    draw_square(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
    uint32_t i;
    uint32_t j;

    j = 0;
    while (j < TILE_SIZE)
    {
        i = 0;
        while (i < TILE_SIZE)
        {
            mlx_put_pixel(img, i + x, j + y, color);
            i++;
        }
        j++;
    }
}

void    update_minimap(void* param)
{
    t_game *data = (t_game*)param;
    uint32_t x;
    uint32_t y;

    // 1. Dibujar Suelo y Techo (Background) [cite: 116]
    y = 0;
    while (data->map.map[y])
    {
        x = 0;
        while (data->map.map[y][x])
        {
            if (data->map.map[y][x] == '1')
                draw_square(data->mlx.img, x * TILE_SIZE, y * TILE_SIZE, data->ceil_rgb);
            else
                draw_square(data->mlx.img, x * TILE_SIZE, y * TILE_SIZE, data->floor_rgb);
            x++;
        }
        y++;
    }

    // 2. Aquí tu compañera llamará a su función:
    // raycasting_loop(data);

    // 3. Manejo de movimiento fluido 
    // handle_input(data);
}

void    update_player(t_game *data)
{
    uint32_t    start_x;
    uint32_t    start_y;
    uint32_t    i;
    uint32_t    j;
    uint32_t    color;

    color = (254 << 24 | 0 << 16 | 0 << 8 | 0xFF);
    start_x = (data->player.pos_x * TILE_SIZE) - (PLAYER_SIZE / 2);
    start_y = (data->player.pos_y * TILE_SIZE) - (PLAYER_SIZE / 2);
    j = 0;
    while (j < PLAYER_SIZE)
    {
        i = 0;
        while (i < PLAYER_SIZE)
        {
            mlx_put_pixel(data->mlx.img, i + start_x, j + start_y, color);
            i++;
        }
        j++;
    }
}

void    render_frame(void *param)
{
    t_game   *data = (t_game*)param;
    
    update_minimap(data);
    update_player(data);
    // 1. Dibujar Suelo y Techo (Background)
    // 2. Ejecutar Raycasting
    // 3. Pintar en cub->screen usando mlx_put_pixel
}

void    hook_key(mlx_key_data_t keydata, void *param)
{
    t_game  *data = (t_game*)param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(data->mlx.mlx);
    handle_input(data);
}

/*
2. El problema visual (Clipping de la cámara)
Tu lógica asume que el jugador es un punto exacto (un píxel matemático sin tamaño).

Imagina que tu jugador está en y = 7.05. El código evalúa (int)7.05 = 7.
Como la casilla 7 es suelo, te deja estar ahí.
El problema real: Estás a 0.05 unidades de distancia del muro (que empieza en el 6.99).
En un motor de Raycasting, el "plano de la cámara" (camera plane) tiene anchura.
Si tu centro está a 0.05 del muro, los bordes de tu cámara van a "atravesar" el muro visualmente.
Verás a través de la pared o la textura se estirará infinitamente y se verá feísimo.

Solución: Por eso se suele sumar un "margen de seguridad" (hitbox) al movimiento,
algo un pelín más grande que tu velocidad de movimiento,
para que el jugador se detenga en 7.2 y nunca llegue a tocar el 7.0.
*/
int is_not_wall(char **map, double y, double x)
{

    if (map[(int)(y + BUFFER)][(int)x] == '1' ||
        map[(int)(y - BUFFER)][(int)x] == '1' ||
        map[(int)y][(int)(x + BUFFER)] == '1' ||
        map[(int)y][(int)(x - BUFFER)] == '1')
        return (0);
    return (1);
}

void    handle_input(t_game *data)
{
    double next_x = data->player.pos_x;
    double next_y = data->player.pos_y;

    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_W))
        next_y -= SPEED;
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_S))
        next_y += SPEED;
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_A))
        next_x -= SPEED;
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_D))
        next_x += SPEED;

    if (is_not_wall(data->map.map, data->player.pos_y, next_x))
        data->player.pos_x = next_x;
    if (is_not_wall(data->map.map, next_y, data->player.pos_x))
        data->player.pos_y = next_y;
}