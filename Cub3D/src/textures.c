/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:18:32 by gfuster           #+#    #+#             */
/*   Updated: 2026/05/27 11:18:41 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	load_textures(t_game *data)
{
	int	i;

	data->mlx.texture[0] = mlx_load_png(data->no_path);
	data->mlx.texture[1] = mlx_load_png(data->so_path);
	data->mlx.texture[2] = mlx_load_png(data->we_path);
	data->mlx.texture[3] = mlx_load_png(data->ea_path);
	i = 0;
	while (i < 4)
	{
		if (!data->mlx.texture[i])
		{
			data->error_msg = "Error: Textures failed to load";
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

mlx_texture_t	*get_wall_texture(t_game *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (data->mlx.texture[3]);
		else
			return (data->mlx.texture[2]);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (data->mlx.texture[1]);
		else
			return (data->mlx.texture[0]);
	}
}
