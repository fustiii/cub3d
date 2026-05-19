#include "../inc/cub3d.h"

static void init_ray_vars(t_game *data, t_ray *ray, int x)
{
    ray->camera_x = (2.0 * x / (double)WIDTH) - 1.0;
    ray->ray_dir_x = data->player.dir_x + (data->player.plane_x * ray->camera_x);
    ray->ray_dir_y = data->player.dir_y + (data->player.plane_y * ray->camera_x);
    ray->map_x = (int)data->player.pos_x;
    ray->map_y = (int)data->player.pos_y;
    
    if (ray->ray_dir_x == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = ft_fabs(1.0 / ray->ray_dir_x);
        
    if (ray->ray_dir_y == 0)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = ft_fabs(1.0 / ray->ray_dir_y);
}

static void calculate_step_and_side_dist(t_game *data, t_ray *ray)
{
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (data->player.pos_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos_x) * ray->delta_dist_x;
    }
    
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (data->player.pos_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - data->player.pos_y) * ray->delta_dist_y;
    }
}

static void dda_algorithm(t_game *data, t_ray *ray)
{
    ray->hit_wall = 0;
    while (ray->hit_wall == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (data->map.map[ray->map_y][ray->map_x] == '1')
            ray->hit_wall = 1;
    }
}

static void calculate_wall_distance(t_game *data, t_ray *ray)
{
    calc_perp_distance(ray);
    calc_screen_coordinates(ray);
    calc_texture_impact(&data->player, ray);
}

//! Sustituida por draw_textued_line
void draw_vertical_line(t_game *data, t_ray *ray, int x)
{
    int y;
    uint32_t color_del_muro; // Un color provisional para probar, ej: 0xFF0000FF (Rojo)

    // 1. Nos situamos en el punto más alto del muro para esta columna
    y = ray->draw_start;
    
    color_del_muro = 0xFF0000FF; // Rojo en formato RGBA para MLX42

    // 2. Bajamos píxel a píxel hasta llegar al final del muro
    while (y <= ray->draw_end)
    {
        // 3. Pintamos el píxel en la imagen principal de tu juego
        // (Asegúrate de que 'data->image' sea el puntero a tu mlx_image_t principal)
        mlx_put_pixel(data->mlx.img, x, y, color_del_muro);
        
        y++;
    }
}

mlx_texture_t   *get_wall_texture(t_game *data, t_ray *ray)
{
    if (ray->side == 0) // Impacto en el eje X (Caras Este / Oeste)
    {
        if (ray->ray_dir_x > 0)
            return (data->mlx.texture[3]);  // El rayo va a la derecha, choca con la pared Oeste del bloque
        else
            return (data->mlx.texture[2]);  // El rayo va a la izquierda, choca con la pared Este
    }
    else // Impacto en el eje Y (Caras Norte / Sur)
    {
        // Invierto estas dos por como he hecho el parseo
        if (ray->ray_dir_y > 0)
            return (data->mlx.texture[1]); // El rayo va hacia abajo, choca con la pared Norte
        else
            return (data->mlx.texture[0]); // El rayo va hacia arriba, choca con la pared Sur
    }
}

void draw_textured_line(t_game *data, t_ray *ray, int x, mlx_texture_t *texture)
{
    int      y;
    int      tex_x;
    int      tex_y;
    double   step;
    double   tex_pos;
    uint32_t color;
    int      index;

    // 1. Calcular la columna de la textura base
    tex_x = (int)(ray->wall_x * (double)texture->width);
    
    // CORRECCIÓN DEL EFECTO ESPEJO:
    // Si chocamos en el eje X y el rayo va a la izquierda...
    if (ray->side == 0 && ray->ray_dir_x < 0)
        tex_x = texture->width - tex_x - 1;
        
    // Si chocamos en el eje Y y el rayo va hacia abajo...
    if (ray->side == 1 && ray->ray_dir_y > 0)
        tex_x = texture->width - tex_x - 1;

    // 2. Calcular factores de escala vertical
    step = 1.0 * texture->height / ray->line_height;
    tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;

    // 3. Bucle de renderizado vertical en la pantalla
    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        // Obtener la fila correspondiente de la textura
        tex_y = (int)tex_pos;
        if (tex_y >= (int)texture->height)
            tex_y = texture->height - 1;
        if (tex_y < 0)
            tex_y = 0;
            
        tex_pos += step;

        // 4. Calcular el índice del array de píxeles (RGBA)
        index = (tex_y * texture->width + tex_x) * texture->bytes_per_pixel;
        
        // Empaquetar los componentes en un uint32_t compatible con MLX42
        color = (texture->pixels[index] << 24) | 
                (texture->pixels[index + 1] << 16) | 
                (texture->pixels[index + 2] << 8) | 
                texture->pixels[index + 3];

        // 5. Pintar en tu imagen principal
        
        mlx_put_pixel(data->mlx.img, x, y, color);
        
        y++;
    }
}

void init_cast_ray(t_game *data)
{
    int             x;
    t_ray           ray;
    mlx_texture_t   *current_tex;

    x = 0;
    while (x < WIDTH)
    {
        init_ray_vars(data, &ray, x);
        calculate_step_and_side_dist(data, &ray);
        dda_algorithm(data, &ray);
        calculate_wall_distance(data, &ray); 
        
        // ==========================================
        // AQUÍ ES DONDE ENTRA TU COMPAÑERO
        // El struct 'ray' ya tiene todo calculado para la columna 'x'.
        // Él deberá crear una función similar a esta y llamarla aquí:
        //
        // draw_vertical_line(data, &ray, x);
        // ==========================================
        current_tex = get_wall_texture(data, &ray);
        draw_textured_line(data, &ray, x, current_tex);
        
        x++;
    }
}