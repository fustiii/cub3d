#include "../inc/cub3d.h"

void    free_all(t_game *data)
{
    free(data->no_path);
    free(data->so_path);
    free(data->we_path);
    free(data->ea_path);

    free_array(data->map.map);
    //Miraro esto y lo que recibo en free textures por si estan bien los punteros
    free_textures(&data->mlx);
}

void    free_textures(t_mlx *mlx)
{
    if (mlx->texture[0])
        mlx_delete_texture(mlx->texture[0]);
    if (mlx->texture[1])
        mlx_delete_texture(mlx->texture[1]);
    if (mlx->texture[2])
        mlx_delete_texture(mlx->texture[2]);
    if (mlx->texture[3])
        mlx_delete_texture(mlx->texture[3]);
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