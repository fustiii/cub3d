#include "../inc/cub3d.h"

t_bres  init_bres(t_point p0, t_point p1)
{
	t_bres b;

	b.dx = abs(p1.x - p0.x);
	b.sx = p0.x < p1.x ? 1 : -1;
	b.dy = -abs(p1.y - p0.y);
	b.sy = p0.y < p1.y ? 1 : -1;
	b.err = b.dx + b.dy;
	return (b);
}

static t_point get_vertex(double cx, double cy, double angle, double size)
{
	t_point p;

	p.x = (int)(cx + cos(angle) * size);
	p.y = (int)(cy + sin(angle) * size);
	return (p);
}

void update_player(t_game *data)
{
	t_point p[3];
	double  cx;
	double  cy;
	double  angle;

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

void    update_minimap(void* param)
{
	t_game *data = (t_game*)param;
	uint32_t x;
	uint32_t y;

	y = 0;
	while (data->map.map[y])
	{
		x = 0;
		while (data->map.map[y][x])
		{
			if (data->map.map[y][x] == '1')
				draw_square(data->mlx.minimap, x * TILE_SIZE, y * TILE_SIZE, 0x00FF00FF);
			else
				draw_square(data->mlx.minimap, x * TILE_SIZE, y * TILE_SIZE, 0xFDFB23FC);
			x++;
		}
		y++;
	}
}