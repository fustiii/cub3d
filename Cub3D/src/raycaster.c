#include "cub3D.h"

int ft_abs(int value)
{
    if (value < 0)
        return(-value);
    return(value);
}

dda_algorithm()
{

}

calculate_step_and_side_dist(t_game *game, int x)
{
    double delta_dist_x;
    double delta_dist_y;
    double step_x;
    double side_dist;

    if(ray_dir_x == 0)
        delta_dist_x = ft_abs(1/ray_dir_x);
    else
        delta_dist_y = 1e30;
    if(ray_dir_y == 0)
        delta_dist_y = 1e30;
    else
        delta_dist_y = ft_abs(1/ray_dir_y);
    if(ray_dir_x > 0)
    {
        step = 1;
        side_dist = (game->player->pos_x - game->map->player_x) * delta_dist_x
    }
    else
    {
        step = -1;
        side_dist = (- game->player->pos_x + game->map->player_x + 1) * delta_dist_x
    }
    if(ray_dir_y > 0)
    {
        step = 1;
        side_dist = (game->player->pos_y - game->map->player_y) * delta_dist_y
    }
    else
    {
        step = -1;
        side_dist = (- game->player->pos_y + game->map->player_y + 1) * delta_dist_y
    }
}

calculate_raydir(t_game *game, int x)
{
    int     camera_x;
    double     ray_dir_x;
    double     ray_dir_y;
    char    *raydir;

    ray->camera_x = (2*x/game->map.cols) - 1;
    ray_dir_x = game->player.dir_x + (game->player.plane_x * camera_x);
    ray_dir_y = game->player.dir_y + (game->player.plane_y * camera_x);
    ray_dir = [ray_dir_x, ray_dir_y];
    return(ray_dir)
}

init_cast_ray(t_game *game)
{
    int     x;
    t_ray   ray;

    x = 0;
    while (x < game->map->cols)
    {

    }
}


