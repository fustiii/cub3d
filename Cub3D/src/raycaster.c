#include "../inc/cub3d.h"

/*
double ft_abs(double value)
{
    if (value < 0)
        return(-value);
    return(value);
}

void dda_algorithm(t_game *game, t_ray *ray)
{
    ray->hit = 0;

    if (ray->delta_dist_x < ray->delta_dist_y)
    {
    }
    else
    {
    }
}

void calculate_step_and_side_dist(t_game *data, t_ray *ray, int x)
{
    if(ray_dir_x == 0)
        delta_dist_y = 1e30;
    else
        delta_dist_x = ft_abs(1/ray_dir_x);
    if(ray_dir_y == 0)
        delta_dist_y = 1e30;
    else
        delta_dist_y = ft_abs(1/ray_dir_y);
    if(ray_dir_x > 0)
    {
        step = -1;
        side_dist = (data->player.pos_x - data->map.player_x) * delta_dist_x;
    }
    else
    {
        step = 1;
        side_dist = (- data->player.pos_x + data->map.player_x + 1) * delta_dist_x;
    }
    if(ray_dir_y > 0)
    {
        step = 1;
        side_dist = (data->player.pos_y - data->map.player_y) * delta_dist_y;
    }
    else
    {
        step = -1;
        side_dist = (- data->player.pos_y + data->map.player_y + 1) * delta_dist_y;
    }
}

void  calculate_raydir(t_game *data, t_ray *ray, int x)
{
    ray->camera_x = (2 * x / (double)WIDTH)) - 1;
    ray->ray_dir_x = data->player.dir_x + (data->player.plane_x * ray->camera_x);
    ray->ray_dir_y = data->player.dir_y + (data->player.plane_y * ray->camera_x);
}

void    init_cast_ray(t_game *data)
{
    int     x;
    t_ray   ray;

    x = 0;
    while (x < WIDTH)
    {

    }
}
*/

