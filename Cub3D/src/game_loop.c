/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:13:06 by gfuster           #+#    #+#             */
/*   Updated: 2026/05/27 11:13:11 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	render_frame(void *param)
{
	t_game	*data;

	data = (t_game *)param;
	draw_background(data);
	update_minimap(data);
	update_player(data);
	init_cast_ray(data);
	handle_input(data);
}

void	hook_key(mlx_key_data_t keydata, void *param)
{
	t_game	*data;

	data = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx.mlx);
}
