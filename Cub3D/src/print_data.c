#include "../inc/cub3d.h"

void    print_data(t_game *data)
{
    printf("ERROR_MSG-> %s\n", data->error_msg);
    printf("NO-> %s\n", data->no_path);
    printf("SO-> %s\n", data->so_path);
    printf("WE-> %s\n", data->we_path);
    printf("EA-> %s\n", data->ea_path);

    printf("F-> %d\n", data->floor_rgb);
    printf("C-> %d\n", data->ceil_rgb);

    int i = 0;
    while (data->map.map != NULL && data->map.map[i] != NULL)
    {
        printf("%s\n", data->map.map[i]);
        i++;
    }

    printf("Rows-> %d\n", data->map.rows);
    printf("Cols-> %d\n", data->map.cols);
    printf("Player_y-> %d\n", data->map.player_y);
    printf("Player_x-> %d\n", data->map.player_x);
    printf("Player_dir-> %c\n", data->map.player_dir);

    printf("Pos_y-> %f\n", data->player.pos_y);
    printf("Pos_x-> %f\n", data->player.pos_x);
    printf("Dir_y-> %f\n", data->player.dir_y);
    printf("Dir_x-> %f\n", data->player.dir_x);
    printf("Plane_y-> %f\n", data->player.plane_y);
    printf("Plane_x-> %f\n", data->player.plane_x);
}