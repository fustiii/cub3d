#include "../inc/cub3d.h"

void    print_data(t_game *data)
{
    printf("ERROR_MSG-> %s\n", data->error_msg);
    printf("NO-> %s\n", data->no_path);
    printf("SO-> %s\n", data->so_path);
    printf("WE-> %s\n", data->we_path);
    printf("EA-> %s\n", data->ea_path);

    printf("F-> %d\n", data->floor_rgb);
}