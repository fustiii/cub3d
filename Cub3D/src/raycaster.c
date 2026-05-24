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

mlx_texture_t   *get_wall_texture(t_game *data, t_ray *ray)
{
    if (ray->side == 0) // Impacto en el eje X (Caras Este / Oeste)
    {
        if (ray->ray_dir_x > 0)
            return (data->mlx.texture[3]);
        else
            return (data->mlx.texture[2]);
    }
    else
    {
        if (ray->ray_dir_y > 0)
            return (data->mlx.texture[1]);
        else
            return (data->mlx.texture[0]);
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
        ft_bzero(&ray, sizeof(t_ray));
        init_ray_vars(data, &ray, x);
        calculate_step_and_side_dist(data, &ray);
        dda_algorithm(data, &ray);
        calculate_wall_distance(data, &ray); 
        current_tex = get_wall_texture(data, &ray);
        draw_textured_line(data, &ray, x, current_tex);
        x++;
    }
}