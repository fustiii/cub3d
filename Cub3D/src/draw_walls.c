#include "../inc/cub3d.h"

static int get_texture_x(t_ray *ray, mlx_texture_t *texture)
{
    int tex_x;

    tex_x = (int)(ray->wall_x * (double)texture->width);
    if ((ray->side == 0 && ray->ray_dir_x < 0) || 
        (ray->side == 1 && ray->ray_dir_y > 0))
    {
        tex_x = texture->width - tex_x - 1;
    }
    return (tex_x);
}

static uint32_t get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
    int index;

    if (tex_y < 0)
        tex_y = 0;
    else if (tex_y >= (int)texture->height)
        tex_y = texture->height - 1;
    if (tex_x < 0)
        tex_x = 0;
    else if (tex_x >= (int)texture->width)
        tex_x = texture->width - 1;

    index = (tex_y * texture->width + tex_x) * texture->bytes_per_pixel;
    
    return ((texture->pixels[index] << 24) | 
            (texture->pixels[index + 1] << 16) | 
            (texture->pixels[index + 2] << 8) | 
            texture->pixels[index + 3]);
}

void draw_textured_line(t_game *data, t_ray *ray, int x, mlx_texture_t *texture)
{
    int      y;
    int      tex_x;
    double   step;
    double   tex_pos;
    uint32_t color;

    tex_x = get_texture_x(ray, texture);
    step = 1.0 * texture->height / ray->line_height;
    tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        color = get_texture_color(texture, tex_x, (int)tex_pos);
        mlx_put_pixel(data->mlx.img, x, y, color);
        tex_pos += step;
        y++;
    }
}