#include "../inc/cub3d.h"

t_type_id find_type_id(const char *line)
{
    if (line == NULL || line[0] == '\0')
        return ID_ERROR;
    // IDs de una sola letra
    if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t')) //!Usar is_space?
        return ID_FLOOR;
    if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
        return ID_CEILING;
    // Seguridad por si la línea solo tiene 1 char
    if (line[1] == '\0')
        return ID_ERROR;
    // IDs de dos letras
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

//!Reducir lineas de la función (igual meter una función de validate dentro de cada if)
int  extract_texture(t_game *data, char *line)
{
    char **tokens;

    tokens = ft_split(line, ' '); // Crea un array en el HEAP
    if (!tokens)
        return (ERROR);
    //! Convertir en ft_strcmp (todas)
    if (strcmp(tokens[0], "NO") == 0)
    { 
        if (data->no_path != NULL)
        {
            data->error_msg = "Error: Type_id NO already exist";
            free_array(tokens);
            return (ERROR);
        }
        //! Convertir en ft_strdup (todas)
        trim_newline(tokens[1]);
        data->no_path = strdup(tokens[1]);
    }
    else if (strcmp(tokens[0], "SO") == 0)
    {
        if (data->so_path != NULL)
        {
            data->error_msg = "Error: Type_id SO already exist";
            free_array(tokens);
            return (ERROR);
        }
        trim_newline(tokens[1]);
        data->so_path = strdup(tokens[1]);
    }
    else if (strcmp(tokens[0], "WE") == 0)
    {
        if (data->we_path != NULL)
        {
            data->error_msg = "Error: Type_id WE already exist";
            free_array(tokens);
            return (ERROR);
        }
        trim_newline(tokens[1]);
        data->we_path = strdup(tokens[1]);
    }
    else if (strcmp(tokens[0], "EA") == 0)
    {
        if (data->ea_path != NULL)
        {
            data->error_msg = "Error: Type_id EA already exist";
            free_array(tokens);
            return (ERROR);
        }
        trim_newline(tokens[1]);
        data->ea_path = strdup(tokens[1]);
    }
    free_array(tokens);
    return (SUCCESS);
}

int  extract_color(t_game *data, char *line)
{
    char    **tokens;
    char    **rgb;

    tokens = ft_split(line, ' '); // Crea un array en el HEAP
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
    //! Convertir en ft_atoi (todas)
    if (strcmp(tokens[0], "F") == 0)
        data->floor_rgb = (atoi(rgb[0]) << 24 | atoi(rgb[1]) << 16 | atoi(rgb[2]) << 8 | 0xFF);
    else if (strcmp(tokens[0], "C") == 0)
        data->ceil_rgb = (atoi(rgb[0]) << 24 | atoi(rgb[1]) << 16 | atoi(rgb[2]) << 8 | 0xFF);
    
    free_array(rgb);
    free_array(tokens);
    return (SUCCESS);
}