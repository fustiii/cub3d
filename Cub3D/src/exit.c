#include "../inc/cub3d.h"

void    exit_mlx(t_mlx *mlx)
{
    int i;

    if (!mlx)
        return;
    if (mlx->img)
         mlx_delete_image(mlx->mlx, mlx->img);
    if (mlx->minimap)
        mlx_delete_image(mlx->mlx, mlx->minimap);
    i = 0;
    while (i < 4)
    {
        if (mlx->texture[i])
            mlx_delete_texture(mlx->texture[i]);
        i++;
    }
    if (mlx->mlx)
        mlx_terminate(mlx->mlx);
}

void exit_error(t_game *data)
{
    // ft_putstr_fd("Error\n", 2);
    // ft_putendl_fd(data->error_msg, 2);
    printf("ERROR_MSG-> %s\n", data->error_msg);
    free_all(data); // Tu función que libera TODO
    exit(EXIT_FAILURE);
}