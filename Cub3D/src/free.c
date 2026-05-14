#include "../inc/cub3d.h"

void    free_all(t_game *data)
{
    free(data->no_path);
    free(data->so_path);
    free(data->we_path);
    free(data->ea_path);

    free_array(data->map.map);
}

void    free_array(char **array)
{
    int i;

    if (!array)
		return ;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

// Llamar a mlx_delete_texture()
// Y revisar que mas deberia borrar...