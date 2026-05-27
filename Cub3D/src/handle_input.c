/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:13:28 by gfuster           #+#    #+#             */
/*   Updated: 2026/05/27 11:13:32 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_not_wall(char **map, double y, double x)
{
	if (map[(int)(y + BUFFER)][(int)x] == '1' ||
		map[(int)(y - BUFFER)][(int)x] == '1' ||
		map[(int)y][(int)(x + BUFFER)] == '1' ||
		map[(int)y][(int)(x - BUFFER)] == '1')
		return (0);
	return (1);
}

static void	player_movement(t_game *data, double *next_x, double *next_y)
{
	if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_W))
	{
		*next_x += data->player.dir_x * SPEED;
		*next_y += data->player.dir_y * SPEED;
	}
	if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_S))
	{
		*next_x -= data->player.dir_x * SPEED;
		*next_y -= data->player.dir_y * SPEED;
	}
	if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_A))
	{
		*next_x += data->player.dir_y * SPEED;
		*next_y -= data->player.dir_x * SPEED;
	}
	if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_D))
	{
		*next_x -= data->player.dir_y * SPEED;
		*next_y += data->player.dir_x * SPEED;
	}
}

static void	camara_rotation(t_game *data)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;

	p = &data->player;
	if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = data->player.dir_x;
		p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
		p->dir_y = old_dir_x * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
		old_plane_x = data->player.plane_x;
		p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
		p->plane_y = old_plane_x * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
	}
	if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_LEFT))
	{
		old_dir_x = data->player.dir_x;
		p->dir_x = p->dir_x * cos(ROT_SPEED) + p->dir_y * sin(ROT_SPEED);
		p->dir_y = -old_dir_x * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
		old_plane_x = data->player.plane_x;
		p->plane_x = p->plane_x * cos(ROT_SPEED) + p->plane_y * sin(ROT_SPEED);
		p->plane_y = -old_plane_x * sin(ROT_SPEED)
			+ p->plane_y * cos(ROT_SPEED);
	}
}

void	handle_input(t_game *data)
{
	double	next_x;
	double	next_y;

	next_x = data->player.pos_x;
	next_y = data->player.pos_y;
	player_movement(data, &next_x, &next_y);
	if (is_not_wall(data->map.map, data->player.pos_y, next_x))
		data->player.pos_x = next_x;
	if (is_not_wall(data->map.map, next_y, data->player.pos_x))
		data->player.pos_y = next_y;
	camara_rotation(data);
}
