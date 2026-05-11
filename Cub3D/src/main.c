#include "../inc/cub3d.h"

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

    //Inicializar las estructuras
    init_data(&data);

    //Leer linea con gnl y parsear info
    if (parse(&data, argv[1]) == ERROR)
        exit_error(&data);

    data.mlx.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
    data.mlx.img = mlx_new_image(data.mlx.mlx , WIDTH, HEIGHT);
    if (!data.mlx.img)
        exit(1);
    mlx_image_to_window(data.mlx.mlx, data.mlx.img, 0, 0);
    
    data.mlx.texture[0] = mlx_load_png(data.no_path);
    data.mlx.texture[1] = mlx_load_png(data.so_path);
    data.mlx.texture[2] = mlx_load_png(data.we_path);
    data.mlx.texture[3] = mlx_load_png(data.ea_path);

    if (!data.mlx.tex[0] || !data.mlx.tex[1] || !data.mlx.tex[2] || !data.mlx.tex[3])
        exit_error(&data);

    mlx_loop_hook(data.mlx.mlx, &hook_render, &data);

    mlx_key_hook(data.mlx.mlx, &hook_key, &data);


    mlx_loop(data.mlx.mlx);
    mlx_terminate(data.mlx.mlx);

    free_all(&data);
    return(EXIT_SUCCESS);
}
