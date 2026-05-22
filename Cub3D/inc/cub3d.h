#ifndef CUB3D_H
# define CUB3D_H

#define SUCCESS 0
#define ERROR -1
#define MAP_DONE 2

#define WIDTH 1500
#define HEIGHT 1000
#define MINIMAP_WIDTH 600
#define MINIMAP_HEIGHT 800

#define TILE_SIZE 16
#define PLAYER_SIZE 8
#define BUFFER 0.2 //Para comprobar su hitbox
// Igual al tamanyo visual del jugador:
// BUFFER = (PLAYER_SIZE / 2.0) / TILE_SIZE
#define SPEED 0.05 //Velocidad de movimiento
#define ROT_SPEED 0.06 // Velocidad de la rotación
// Que realmente seria el angulo que queremos rotar el vector cada vez

#include <unistd.h> //close, read, write
#include <fcntl.h> //open
#include <errno.h> //errno
#include <stdio.h> //printf, perror
#include <stdlib.h> //malloc, free, exit
#include <string.h> //strerror
#include <sys/time.h> //gettimeofday
#include <math.h> // para las funciones matematicas
#include "get_next_line.h" // para gnl
#include "../Libft/libft/libft.h"
#include "MLX42/MLX42.h" // para mlx


typedef enum
{
    ID_ERROR = 0,
    ID_NORTH,	// NO
    ID_SOUTH,	// SO
    ID_WEST,	// WE
    ID_EAST,	// EA
    ID_FLOOR,	// F
    ID_CEILING	// C
}	t_type_id;

// Coordenadas update jugador en minimapa
typedef struct s_point
{
    int x;
    int y;
}   t_point;

// Variables del algoritmo de Bresenham
typedef struct s_bres
{
    int dx;
    int sx;
    int dy;
    int sy;
    int err;
}   t_bres;

// Para calcular distancias
typedef struct	s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
    double	delta_dist_y;
    int		step_x;
	int		step_y;
	int		side;
    double	side_dist_x;
    double	side_dist_y;
	int		hit_wall;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
}			t_ray;

// Posición física del jugador en el mapa
typedef struct	s_player
{
	double	pos_y;    // Posición real
	double	pos_x;    // Posición real
	double	dir_y;    // Vector de dirección
	double	dir_x;    // Vector de dirección
	double	plane_y;  // Plano cámara (FOV = field of view)
	double	plane_x;  // Plano cámara
}			t_player;

typedef struct	s_map
{
	char	**map;      // El mapa en sí (matriz de strings)
	int		rows;        // Filas
	int		cols;        // Columnas
	int		player_y;    // Posición Y
	int		player_x;    // Posición X
	char	player_dir;  // N, S, E, W
}			t_map;

typedef struct	s_mlx
{
	mlx_t			*mlx;        // Puntero a la ventana
	mlx_image_t		*img;        // Puntero a la imagen
	mlx_image_t		*minimap;    // Puntero al minimapa
	mlx_texture_t	*texture[4]; // Punteros a las texturas
}					t_mlx;

typedef struct	s_game
{
	char		*no_path;    // Ruta textura Norte
	char		*so_path;    // Ruta textura Sur
	char		*we_path;    // Ruta textura Oeste
	char		*ea_path;    // Ruta textura Este
	uint32_t	floor_rgb;   // R, G, B suelo
	uint32_t	ceil_rgb;    // R, G, B techo
	char		*error_msg;
	t_map		map;         // Estructura del mapa
	t_player	player;      // Estructura del jugador
	t_mlx		mlx;         // Estructura de mlx
}				t_game;



void		init_data(t_game *data);

/* -- PARSING -- */
//PARSE_MAIN
int			parse(t_game *data, char *file);
int			fill_data(char **file_content, t_game *data);
int			process_line(char *line, t_game *data, int *ids_found, char **file_content);
int			is_empty(char *line);

//PARSE_ELEMENTS
t_type_id	find_type_id(const char *line);
int			extract_texture(t_game *data, char *line);
int			extract_color(t_game *data, char *line);

//PARSE_MAP
int			extract_map(t_game *data, char **map);
int			flood_fill(t_game *data);

//FILE_READER
int 		count_lines(int fd);
int 		open_file(t_game *data, const char *pathname);
char    	**file_to_array(t_game *data, char *file);

//VALIDATIONS
int    		validate_identifiers(t_game *data);
int 		validate_map(t_game *data);
int			validate_color(t_game *data, char **rgb, char *token);


//FUNCTIONS MLX
int			load_textures(t_game *data);
void		render_frame(void* param);
void		hook_key(mlx_key_data_t keydata, void* param);
void		handle_input(t_game *data);

//PAINT SCREEN
void		update_minimap(void* param);
void		update_player(t_game *data);
void		draw_background(t_game *data);
void		draw_textured_line(t_game *data, t_ray *ray, int x, mlx_texture_t *texture);
void		draw_line(t_game *data, t_point p0, t_point p1, uint32_t color);
void		draw_square(mlx_image_t *minimap, uint32_t x, uint32_t y, uint32_t color);

//UTILS
char		**ft_split(char const *str, char c);
void		print_data(t_game *data);
void		trim_newline(char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			is_space(char c);

//FREE
void    	free_array(char **array);
void    	free_all(t_game *data);
void		free_textures(t_mlx *mlx);

//RAYCASTER
void		init_cast_ray(t_game *data);

//RAYCASTER AUX
double		ft_fabs(double value);
void		calc_perp_distance(t_ray *ray);
void		calc_screen_coordinates(t_ray *ray);
void		calc_texture_impact(t_player *player, t_ray *ray);

//EXIT
void exit_error(t_game *data);
void    exit_mlx(t_mlx *mlx);

t_bres		init_bres(t_point p0, t_point p1);


#endif
