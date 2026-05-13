#ifndef CUB3D_H
# define CUB3D_H

#define SUCCESS 0
#define ERROR -1
#define MAP_DONE 2

#define WIDTH 1080
#define HEIGHT 720

#define TILE_SIZE 32
#define PLAYER_SIZE 6

#include <unistd.h> //close, read, write
#include <fcntl.h> //open
#include <errno.h> //errno
#include <stdio.h> //printf, perror
#include <stdlib.h> //malloc, free, exit
#include <string.h> //strerror
#include <sys/time.h> //gettimeofday
#include "get_next_line.h" // para gnl
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

typedef struct	s_map
{
	char	**map;      // El mapa en sí (matriz de strings)
	int		rows;        // Filas
	int		cols;        // Columnas
	int		player_y;    // Posición Y
	int		player_x;    // Posición X
	char	player_dir;  // N, S, E, W
}			t_map;

typedef struct	s_player
{
	double	pos_y;    // Posición real
	double	pos_x;    // Posición real
	double	dir_y;    // Vector de dirección
	double	dir_x;    // Vector de dirección
	double	plane_y;  // Plano cámara
	double	plane_x;  // Plano cámara
}			t_player;

typedef struct	s_mlx
{
	mlx_t			*mlx;    // Puntero a la ventana
	mlx_image_t		*img;    // Puntero a la imagen
	xpm_t			*texture[4]; // Punteros a las texturas
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
void		load_textures(t_game *data);
void		render_frame(void* param);
void		hook_key(mlx_key_data_t keydata, void* param);
void		handle_input(t_game *data);
//UTILS
char		**ft_split(char const *str, char c);
void		print_data(t_game *data);
void		trim_newline(char *str);


//FREE
void    	free_array(char **array);
void    	free_all(t_game *data);



#endif
