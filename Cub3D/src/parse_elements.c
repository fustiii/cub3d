#include "../inc/cub3d.h"

t_type_id find_type_id(const char *line)
{
	if (line == NULL || line[0] == '\0')
		return ID_ERROR;
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return ID_FLOOR;
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return ID_CEILING;
	if (line[1] == '\0')
		return ID_ERROR;
	if (line[0] == 'N' && line[1] == 'O')
		return ID_NORTH;
	if (line[0] == 'S' && line[1] == 'O')
		return ID_SOUTH;
	if (line[0] == 'W' && line[1] == 'E')
		return ID_WEST;
	if (line[0] == 'E' && line[1] == 'A')
		return ID_EAST;
	return ID_ERROR;
}

static int	assign_path(char **target_path, char *path, t_game *data, char *err_msg)
{
	if (*target_path != NULL)
	{
		data->error_msg = err_msg;
		return (ERROR);
	}
	trim_newline(path);
	*target_path = ft_strdup(path);
	if (!*target_path)
		return (ERROR);
	return (SUCCESS);
}

int	extract_texture(t_game *data, char *line)
{
	char	**tokens;
	int		status;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (ERROR);
	status = SUCCESS;
	if (ft_strcmp(tokens[0], "NO") == 0)
		status = assign_path(&data->no_path, tokens[1], data, "Error: NO already exist");
	else if (ft_strcmp(tokens[0], "SO") == 0)
		status = assign_path(&data->so_path, tokens[1], data, "Error: SO already exist");
	else if (ft_strcmp(tokens[0], "WE") == 0)
		status = assign_path(&data->we_path, tokens[1], data, "Error: WE already exist");
	else if (ft_strcmp(tokens[0], "EA") == 0)
		status = assign_path(&data->ea_path, tokens[1], data, "Error: EA already exist");
	free_array(tokens);
	return (status);
}

int  extract_color(t_game *data, char *line)
{
	char    **tokens;
	char    **rgb;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (ERROR);
	rgb = ft_split(tokens[1], ',');
	if (!rgb)
	{
		free_array(tokens);
		return (ERROR);
	}
	if (validate_color(data, rgb, tokens[1]) == ERROR)
	{
		free_array(rgb);
		free_array(tokens);
		return (ERROR);
	}
	if (ft_strcmp(tokens[0], "F") == 0)
		data->floor_rgb = (atoi(rgb[0]) << 24 | atoi(rgb[1]) << 16 | atoi(rgb[2]) << 8 | 0xFF);
	else if (ft_strcmp(tokens[0], "C") == 0)
		data->ceil_rgb = (atoi(rgb[0]) << 24 | atoi(rgb[1]) << 16 | atoi(rgb[2]) << 8 | 0xFF);
	free_array(rgb);
	free_array(tokens);
	return (SUCCESS);
}