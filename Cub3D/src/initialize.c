#include "../inc/cub3d.h"

void init_data(t_game *data)
{
    // Inicializar texturas
    data->no_path = NULL;
    data->so_path = NULL;
    data->we_path = NULL;
    data->ea_path = NULL;
    
    // Inicializar colores con un valor imposible
    data->floor_rgb = -1;
    data->ceil_rgb = -1;

    // Inicializar error
    data->error_msg = NULL;

    // Inicializar la sub-estructura map
    data->map.map = NULL;
    data->map.rows = 0;
    data->map.cols = 0;
    data->map.player_x = -1;
    data->map.player_y = -1;
    data->map.player_dir = -1;
}