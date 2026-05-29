/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 18:28:13 by gfuster           #+#    #+#             */
/*   Updated: 2026/05/29 18:28:15 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SUCCESS 0
# define ERROR -1
# define CONTINUE 1
# define MAP_START 2

# define WIDTH 1500
# define HEIGHT 1000
# define MINIMAP_WIDTH 600
# define MINIMAP_HEIGHT 800

# define TILE_SIZE 16
# define PLAYER_SIZE 8
# define BUFFER 0.2
# define SPEED 0.05
# define ROT_SPEED 0.06

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h> 
# include <math.h>
# include "get_next_line.h"
# include "../Libft/libft/libft.h"
# include "MLX42/MLX42.h"

typedef enum e_type_id
{
	ID_ERROR = 0,
	ID_NORTH,
	ID_SOUTH,
	ID_WEST,
	ID_EAST,
	ID_FLOOR,
	ID_CEILING
}	t_type_id;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_bres
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
}	t_bres;

typedef struct s_ray
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
}	t_ray;

typedef struct s_player
{
	double	pos_y;
	double	pos_x;
	double	dir_y;
	double	dir_x;
	double	plane_y;
	double	plane_x;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		rows;
	int		cols;
	int		player_y;
	int		player_x;
	char	player_dir;
}	t_map;

typedef struct s_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*minimap;
	mlx_texture_t	*texture[4];
}	t_mlx;

typedef struct s_game
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	uint32_t	floor_rgb;
	uint32_t	ceil_rgb;
	char		*error_msg;
	t_map		map;
	t_player	player;
	t_mlx		mlx;
}	t_game;

void			init_data(t_game *data);

/* -- PARSING -- */
//PARSE_MAIN
int				parse(t_game *data, char *file);
int				fill_data(char **file_content, t_game *data);
int				is_empty(char *line);

//PARSE_ELEMENTS
t_type_id		find_type_id(const char *line);
int				extract_texture(t_game *data, char *line);
int				extract_color(t_game *data, char *line);

//PARSE_MAP
int				extract_map(t_game *data, char **map);
int				flood_fill(t_game *data);
int				assign_player_data(t_game *data, int y, int x);
int				allowed_character(char pos);

//INIT_PLAYER
void			synchronize_player(t_game *data);

//FILE_READER
int				count_lines(int fd);
int				open_file(t_game *data, const char *pathname);
char			**file_to_array(t_game *data, char *file);

//VALIDATIONS
int				validate_identifiers(t_game *data);
int				validate_map(t_game *data);
int				validate_color(t_game *data, char **rgb, char *token);
int				has_extension(char *path, char *end);

//FUNCTIONS MLX
void			start_game_graphics(t_game *data);
int				load_textures(t_game *data);
void			render_frame(void *param);
void			hook_key(mlx_key_data_t keydata, void *param);
void			handle_input(t_game *data);

//PAINT SCREEN
void			update_minimap(void *param);
void			update_player(t_game *data);
void			draw_background(t_game *data);
void			draw_textured_line(t_game *g, t_ray *r,
					int x, mlx_texture_t *t);
void			draw_line(t_game *data, t_point p0, t_point p1, uint32_t color);
void			draw_square(mlx_image_t *map, uint32_t x,
					uint32_t y, uint32_t c);

//UTILS
char			**ft_split(char const *str, char c);
char			**ft_split_whitespace(char const *str);
void			print_data(t_game *data);
void			trim_newline(char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				is_space(char c);
int				is_walkable(char c);

//FREE
void			free_array(char **array);
void			free_all(t_game *data);
void			free_textures(t_mlx *mlx);

//RAYCASTER
void			init_cast_ray(t_game *data);

//RAYCASTER AUX
double			ft_fabs(double value);
void			calc_perp_distance(t_ray *ray);
void			calc_screen_coordinates(t_ray *ray);
void			calc_texture_impact(t_player *player, t_ray *ray);
mlx_texture_t	*get_wall_texture(t_game *data, t_ray *ray);

//EXIT
void			exit_error(t_game *data);
void			exit_mlx(t_mlx *mlx);
int				free_and_return(char **tokens, char **rgb, int status);

t_bres			init_bres(t_point p0, t_point p1);

#endif
