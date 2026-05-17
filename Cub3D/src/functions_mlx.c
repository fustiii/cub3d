#include "../inc/cub3d.h"

void    load_textures(t_game *data)
{
    int i;
    data->mlx.texture[0] = mlx_load_png(data->no_path);
    data->mlx.texture[1] = mlx_load_png(data->so_path);
    data->mlx.texture[2] = mlx_load_png(data->we_path);
    data->mlx.texture[3] = mlx_load_png(data->ea_path);
    {
        if (!data->mlx.texture[0] || !data->mlx.texture[1] ||
               !data->mlx.texture[2] || !data->mlx.texture[3])
        {
            i = 0;
            while (i < 4)
            {
                //Mirar como printar error personalizado
                //printf("Error: No se pudo cargar la textura EA (Ruta: %s)\n", data->ea_path);
                exit(1);
                //exit_error(&data);
                i++;
            }
        }
    }
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

void    draw_triangle(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
    uint32_t i;
    uint32_t j;

    j = 0;
    while (j < TILE_SIZE)
    {
        i = 0;
        // Al hacer que i dependa de j, cada fila dibuja un píxel más que la anterior
        while (i <= j) 
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

    // 1. Dibujar Suelo y Techo (Background)
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

/* He actualizado update player para que en el minimapa se muestre un
triangulo apuntando hacia donde mira el jugador*/

// Usando el Algoritmo de Bresenham
void draw_line(t_game *data, int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        // Pintamos el píxel en la imagen del juego
        // NOTA: Cambia 'img' si en tu t_mlx se llama diferente
        mlx_put_pixel(data->mlx.img, x0, y0, color);
        
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void    update_player(t_game *data)
{
    uint32_t    color;
    double      center_x;
    double      center_y;
    double      angle;
    int         x1, y1, x2, y2, x3, y3; 

    // Color rojo en formato RGBA (dependiendo de tu versión de MLX42)
    color = (254 << 24 | 0 << 16 | 0 << 8 | 0xFF); 

    // 1. Centro del jugador en el minimapa usando sus coordenadas reales
    center_x = data->player.pos_x * TILE_SIZE;
    center_y = data->player.pos_y * TILE_SIZE;

    // 2. Calculamos el ángulo actual a partir del vector dir_x y dir_y
    angle = atan2(data->player.dir_y, data->player.dir_x); 

    // 3. Calculamos los 3 vértices del triángulo apuntando hacia la dirección
    // Vértice 1: La punta frontal
    x1 = center_x + cos(angle) * PLAYER_SIZE;
    y1 = center_y + sin(angle) * PLAYER_SIZE;

    // Vértice 2: Esquina trasera izquierda (rotada ~140 grados)
    x2 = center_x + cos(angle + 2.5) * (PLAYER_SIZE / 2);
    y2 = center_y + sin(angle + 2.5) * (PLAYER_SIZE / 2);

    // Vértice 3: Esquina trasera derecha (rotada ~-140 grados)
    x3 = center_x + cos(angle - 2.5) * (PLAYER_SIZE / 2);
    y3 = center_y + sin(angle - 2.5) * (PLAYER_SIZE / 2);

    // 4. Dibujamos el contorno del triángulo uniendo los puntos
    draw_line(data, x1, y1, x2, y2, color);
    draw_line(data, x2, y2, x3, y3, color);
    draw_line(data, x3, y3, x1, y1, color);
}
/*
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
*/
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
/*
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
*/
void handle_input(t_game *data)
{
    double next_x = data->player.pos_x;
    double next_y = data->player.pos_y;
    double old_dir_x;
    double old_plane_x;

    // 1. MOVIMIENTO HACIA ADELANTE Y ATRÁS (Relativo a la cámara)
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_W))
    {
        next_x += data->player.dir_x * SPEED;
        next_y += data->player.dir_y * SPEED;
    }
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_S))
    {
        next_x -= data->player.dir_x * SPEED;
        next_y -= data->player.dir_y * SPEED;
    }

    // Comprobación de colisiones antes de aplicar el movimiento
    if (is_not_wall(data->map.map, data->player.pos_y, next_x))
        data->player.pos_x = next_x;
    if (is_not_wall(data->map.map, next_y, data->player.pos_x))
        data->player.pos_y = next_y;

    // Rotar camara a la derecha
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_D))
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
    if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_A))
    {
        // Para girar al lado contrario, invertimos los signos que multiplican al sin()
        old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(ROT_SPEED) + data->player.dir_y * sin(ROT_SPEED);
        data->player.dir_y = -old_dir_x * sin(ROT_SPEED) + data->player.dir_y * cos(ROT_SPEED);

        old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(ROT_SPEED) + data->player.plane_y * sin(ROT_SPEED);
        data->player.plane_y = -old_plane_x * sin(ROT_SPEED) + data->player.plane_y * cos(ROT_SPEED);
    }
}