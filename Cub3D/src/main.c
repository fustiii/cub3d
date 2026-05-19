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

int main(int argc, char **argv)
{
    t_game   data;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file.cub>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Inicializar las estructuras
    init_data(&data);

    // Leer linea con gnl y parsear info
    if (parse(&data, argv[1]) == ERROR)
        exit_error(&data);


    // Inicialiazmos la nueva ventana
    data.mlx.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
    if (!data.mlx.mlx)
    {
        data.error_msg = "Error: Failed to initialize MLX library";
        exit_error(&data);
    }
    // Creamos una imagen (donde pintaremos los pixeles)
    data.mlx.img = mlx_new_image(data.mlx.mlx , WIDTH, HEIGHT);
    if (!data.mlx.img)
    {
        data.error_msg = "Error: Failed to create MLX image buffer";
        //mlx_terminate(data.mlx.mlx);
        exit_mlx(&data.mlx);
        exit_error(&data);
    }
    data.mlx.minimap = mlx_new_image(data.mlx.mlx , MINIMAP_WIDTH, MINIMAP_HEIGHT);
    if (!data.mlx.minimap)
    {
        data.error_msg = "Error: Failed to create MLX image buffer";
        //mlx_delete_image(data.mlx.mlx, data.mlx.img);
        //mlx_terminate(data.mlx.mlx);
        exit_mlx(&data.mlx);
        exit_error(&data);
    }
    // Ponemos la imagen en la ventana
    mlx_image_to_window(data.mlx.mlx, data.mlx.img, 0, 0);
    mlx_image_to_window(data.mlx.mlx, data.mlx.minimap, 0, 0);
    
    //Cargamos las texturas
    if (load_textures(&data) == ERROR)
    {
        exit_mlx(&data.mlx);
        exit_error(&data);
    }
    
    // Tareas que vamos a ejecutar
    mlx_loop_hook(data.mlx.mlx, &render_frame, &data);

    
    // Registra cuando pulsamos alguna tecla
    mlx_key_hook(data.mlx.mlx, &hook_key, &data);
    

    mlx_loop(data.mlx.mlx);

    /*
    mlx_delete_image(data.mlx.mlx, data.mlx.img);
    mlx_delete_image(data.mlx.mlx, data.mlx.minimap);
    mlx_terminate(data.mlx.mlx);
    */
    exit_mlx(&data.mlx);
    free_all(&data);
    return(EXIT_SUCCESS);
}