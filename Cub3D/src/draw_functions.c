#include "../inc/cub3d.h"

/*
Dibuja una línea usando el algoritmo de Bresenham.
 */
void draw_line(t_game *data, t_point p0, t_point p1, uint32_t color)
{
    t_bres b;
    int    e2;

    b = init_bres(p0, p1);
    while (1)
    {
        mlx_put_pixel(data->mlx.minimap, p0.x, p0.y, color);
        if (p0.x == p1.x && p0.y == p1.y)
            break ;
        e2 = 2 * b.err;
        if (e2 >= b.dy)
        {
            b.err += b.dy;
            p0.x += b.sx;
        }
        if (e2 <= b.dx)
        {
            b.err += b.dx;
            p0.y += b.sy;
        }
    }
}

void    draw_square(mlx_image_t *minimap, uint32_t x, uint32_t y, uint32_t color)
{
    uint32_t i;
    uint32_t j;

    j = 0;
    while (j < TILE_SIZE)
    {
        i = 0;
        while (i < TILE_SIZE)
        {
            mlx_put_pixel(minimap, i + x, j + y, color);
            i++;
        }
        j++;
    }
}

void    draw_background(t_game *data)
{
    int y;
    int x;

    y = 0;
    while (y < HEIGHT / 2)
    {
        x = 0;
        while (x < WIDTH)
        {
            mlx_put_pixel(data->mlx.img, x, y, data->ceil_rgb);
            x++;
        }
        y++;
    }
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            mlx_put_pixel(data->mlx.img, x, y, data->floor_rgb);
            x++;
        }
        y++;
    }
}