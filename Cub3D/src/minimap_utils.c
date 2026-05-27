/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:14:39 by gfuster           #+#    #+#             */
/*   Updated: 2026/05/27 11:14:43 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_bres	init_bres(t_point p0, t_point p1)
{
	t_bres	b;

	b.dx = abs(p1.x - p0.x);
	if (p0.x < p1.x)
		b.sx = 1;
	else
		b.sx = -1;
	b.dy = -abs(p1.y - p0.y);
	if (p0.y < p1.y)
		b.sy = 1;
	else
		b.sy = -1;
	b.err = b.dx + b.dy;
	return (b);
}

static t_point	get_vertex(double cx, double cy, double angle, double size)
{
	t_point	p;

	p.x = (int)(cx + cos(angle) * size);
	p.y = (int)(cy + sin(angle) * size);
	return (p);
}

void	update_player(t_game *data)
{
	t_point	p[3];
	double	cx;
	double	cy;
	double	angle;

	if ((data->map.cols * TILE_SIZE) > MINIMAP_WIDTH
		|| (data->map.rows * TILE_SIZE) > MINIMAP_HEIGHT)
		return ;

	cx = data->player.pos_x * TILE_SIZE;
	cy = data->player.pos_y * TILE_SIZE;
	angle = atan2(data->player.dir_y, data->player.dir_x);
	p[0] = get_vertex(cx, cy, angle, PLAYER_SIZE);
	p[1] = get_vertex(cx, cy, angle + 2.5, PLAYER_SIZE / 2.0);
	p[2] = get_vertex(cx, cy, angle - 2.5, PLAYER_SIZE / 2.0);
	draw_line(data, p[0], p[1], 0xFE0000FF);
	draw_line(data, p[1], p[2], 0xFE0000FF);
	draw_line(data, p[2], p[0], 0xFE0000FF);
}

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	update_minimap(void *param)
{
	t_game		*data;
	uint32_t	x;
	uint32_t	y;

	data = (t_game *)param;

	if ((data->map.cols * TILE_SIZE) > MINIMAP_WIDTH
		|| (data->map.rows * TILE_SIZE) > MINIMAP_HEIGHT)
		return ;

	y = 0;
	while (data->map.map[y])
	{
		x = 0;
		while (data->map.map[y][x])
		{
			if (data->map.map[y][x] == '1')
				draw_square(data->mlx.minimap, x * TILE_SIZE,
					y * TILE_SIZE, 0x00FF00FF);
			else if (is_walkable(data->map.map[y][x]))
				draw_square(data->mlx.minimap, x * TILE_SIZE,
					y * TILE_SIZE, 0xFDFB23FC);
			x++;
		}
		y++;
	}
}