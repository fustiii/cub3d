/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:19:25 by gfuster           #+#    #+#             */
/*   Updated: 2026/05/27 11:19:26 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_valid_byte(char *str)
{
	int	value;

	value = ft_atoi(str);
	if (value >= 0 && value <= 255)
		return (1);
	return (0);
}

static int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r' || str[i] == ' ')
			break ;
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

static int	count_char_ocurrences(char *token, char c)
{
	char	*ptr;
	int		commas;

	commas = 0;
	ptr = ft_strchr(token, c);
	while (ptr != NULL)
	{
		commas++;
		ptr++;
		ptr = ft_strchr(ptr, c);
	}
	return (commas);
}

static int	set_error(t_game *data, char *msg)
{
	data->error_msg = msg;
	return (ERROR);
}

int	validate_color(t_game *data, char **rgb, char *token)
{
	int	i;

	if (count_char_ocurrences(token, ',') != 2)
		return (set_error(data, "Error: More than two commas"));
	i = -1;
	while (rgb[++i])
	{
		if (!is_str_digit(rgb[i]))
			return (set_error(data, "Error: Is not a digit"));
		if (!is_valid_byte(rgb[i]))
			return (set_error(data, "Error: Is not a valid byte [0-255]"));
	}
	if (i != 3)
		return (set_error(data, "Error: Too many or too few color"));
	return (SUCCESS);
}
