/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfuster <gfuster@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:15:33 by gfuster           #+#    #+#             */
/*   Updated: 2026/05/27 11:16:03 by gfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	process_identifier(char *line, t_game *data, int *ids_found)
{
	t_type_id	type_id;

	type_id = find_type_id(line);
	if (type_id == ID_ERROR)
		return (CONTINUE);
	if (type_id == ID_FLOOR || type_id == ID_CEILING)
	{
		if (extract_color(data, line) == ERROR)
			return (ERROR);
	}
	else
	{
		if (extract_texture(data, line) == ERROR)
			return (ERROR);
	}
	(*ids_found)++;
	return (SUCCESS);
}

static int	process_line(char *line, t_game *data, int *ids_found)
{
	int		id_status;

	if (is_empty(line))
		return (SUCCESS);
	trim_newline(line);
	id_status = process_identifier(line, data, ids_found);
	if (id_status == ERROR)
		return (ERROR);
	if (id_status == SUCCESS)
		return (SUCCESS);
	if (*ids_found < 6)
	{
		data->error_msg = "Error: Invalid ID or missing elements before map";
		return (ERROR);
	}
	return (MAP_START);
}

static int	process_map(char **file_content, t_game *data, int index)
{
	if (validate_identifiers(data) == ERROR)
		return (ERROR);
	if (extract_map(data, &file_content[index]) == ERROR)
		return (ERROR);
	if (validate_map(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	fill_data(char **file_content, t_game *data)
{
	int	i;
	int	ids_found;
	int	status;

	i = 0;
	ids_found = 0;
	status = SUCCESS;
	while (file_content[i])
	{
		status = process_line(file_content[i], data, &ids_found);
		if (status == ERROR)
			return (ERROR);
		if (status == MAP_START)
			break ;
		i++;
	}
	if (status != MAP_START)
	{
		data->error_msg = "Error: Map content not found";
		return (ERROR);
	}
	return (process_map(file_content, data, i));
}

int	parse(t_game *data, char *file)
{
	char	**file_content;

	file_content = file_to_array(data, file);
	if (!file_content)
		return (ERROR);
	if (fill_data(file_content, data) == ERROR)
	{
		free_array(file_content);
		return (ERROR);
	}
	synchronize_player(data);
	free_array(file_content);
	return (SUCCESS);
}
