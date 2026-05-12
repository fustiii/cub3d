#include "cub3D.h"

// Crea un mapa falso de 5x5 rodeado de unos
char *mock_map_data[] = {
    "11111",
    "10001",
    "10001",
    "10001",
    "11111"
};

void setup_mock_game(t_game *game)
{
    // Configurar mapa
    game->map.map = mock_map_data;
    game->map.cols = 5;
    game->map.rows = 5;

    // Configurar jugador en el centro del mapa
    game->player.pos_x = 2.5;
    game->player.pos_y = 2.5;

    // Mirando hacia el Norte (Vector de dirección)
    game->player.dir_x = 0.0;
    game->player.dir_y = -1.0;

    // Plano de cámara para un FOV de aprox 66 grados
    game->player.plane_x = 0.66;
    game->player.plane_y = 0.0;
}

int main(void)
{
    t_game  game;
    t_ray   ray;
    int     x;

    setup_mock_game(&game);

    // Simulamos calcular el rayo central de una pantalla de 1080px (WIDTH)
    x = 1080 / 2; 
    
    // Aquí llamarás a tus funciones matemáticas:
    // init_ray_calc(&game.player, &ray, x);
    // calculate_step_and_side_dist(&game.player, &ray);
    // perform_dda(&game.map, &ray);
    // calculate_wall_distance(&ray);
    
    // printf("Distancia al muro central: %f\n", ray.perp_wall_dist);

    return (0);
}