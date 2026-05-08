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
    free_all(&data);
}