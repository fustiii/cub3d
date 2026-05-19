#include "../inc/cub3d.h"

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
static int is_not_wall(char **map, double y, double x)
{

    if (map[(int)(y + BUFFER)][(int)x] == '1' ||
        map[(int)(y - BUFFER)][(int)x] == '1' ||
        map[(int)y][(int)(x + BUFFER)] == '1' ||
        map[(int)y][(int)(x - BUFFER)] == '1')
        return (0);
    return (1);
}

static void player_movement(t_game *data, double *next_x, double *next_y)
{
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_W))
    {
        *next_x += data->player.dir_x * SPEED;
        *next_y += data->player.dir_y * SPEED;
    }
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_S))
    {
        *next_x -= data->player.dir_x * SPEED;
        *next_y -= data->player.dir_y * SPEED;
    }
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_A))
    {
        *next_x += data->player.dir_y * SPEED;
        *next_y -= data->player.dir_x * SPEED;
    }
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_D))
    {
        *next_x -= data->player.dir_y * SPEED;
        *next_y += data->player.dir_x * SPEED;
    }
}

static void camara_rotation(t_game *data)
{
    double  old_dir_x;
    double  old_plane_x;

    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_RIGHT))
    {
        // Rotamos el vector de dirección
        old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(ROT_SPEED) - data->player.dir_y * sin(ROT_SPEED);
        data->player.dir_y = old_dir_x * sin(ROT_SPEED) + data->player.dir_y * cos(ROT_SPEED);
        // Rotamos el plano de la cámara exactamente igual
        old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(ROT_SPEED) - data->player.plane_y * sin(ROT_SPEED);
        data->player.plane_y = old_plane_x * sin(ROT_SPEED) + data->player.plane_y * cos(ROT_SPEED);
    }
    // Rotar camara a la izquierda
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_LEFT))
    {
        old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(ROT_SPEED) + data->player.dir_y * sin(ROT_SPEED);
        data->player.dir_y = -old_dir_x * sin(ROT_SPEED) + data->player.dir_y * cos(ROT_SPEED);
        old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(ROT_SPEED) + data->player.plane_y * sin(ROT_SPEED);
        data->player.plane_y = -old_plane_x * sin(ROT_SPEED) + data->player.plane_y * cos(ROT_SPEED);
    }
}

void handle_input(t_game *data)
{
    double  next_x;
    double  next_y;

    next_x = data->player.pos_x;
    next_y = data->player.pos_y;
    // Movimiento del jugador (Relativo a la cámara)
    player_movement(data, &next_x, &next_y);

    // Comprobación de colisiones antes de aplicar el movimiento
    if (is_not_wall(data->map.map, data->player.pos_y, next_x))
        data->player.pos_x = next_x;
    if (is_not_wall(data->map.map, next_y, data->player.pos_x))
        data->player.pos_y = next_y;

    // Rotación de la cámara
    camara_rotation(data);
}