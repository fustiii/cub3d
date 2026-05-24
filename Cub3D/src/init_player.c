#include "../inc/cub3d.h"

void synchronize_player(t_game *data)
{
    if (data->map.player_dir == 'N')
    {
        data->player.dir_y = -1.0;
        data->player.plane_x = 0.66;
    }
    else if (data->map.player_dir == 'S')
    {
        data->player.dir_y = 1.0;
        data->player.plane_x = -0.66;
    }
    else if (data->map.player_dir == 'E')
    {
        data->player.dir_x = 1.0;
        data->player.plane_y = 0.66;
    }
    else if (data->map.player_dir == 'W')
    {
        data->player.dir_x = -1.0;
        data->player.plane_y = -0.66;
    }
    data->player.pos_x = (double)data->map.player_x + 0.5;
    data->player.pos_y = (double)data->map.player_y + 0.5;
}