/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:09:15 by gfuster           #+#    #+#             */
/*   Updated: 2026/05/27 11:09:17 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	free_and_return(char **tokens, char **rgb, int status)
{
	if (rgb)
		free_array(rgb);
	if (tokens)
		free_array(tokens);
	return (status);
}

void	exit_mlx(t_mlx *mlx)
{
	int	i;

	if (!mlx)
		return ;
	if (mlx->img)
		mlx_delete_image(mlx->mlx, mlx->img);
	if (mlx->minimap)
		mlx_delete_image(mlx->mlx, mlx->minimap);
	i = 0;
	while (i < 4)
	{
		if (mlx->texture[i])
			mlx_delete_texture(mlx->texture[i]);
		i++;
	}
	if (mlx->mlx)
		mlx_terminate(mlx->mlx);
}

void	exit_error(t_game *data)
{
	ft_putendl_fd(data->error_msg, 2);
	free_all(data);
	exit(EXIT_FAILURE);
}
