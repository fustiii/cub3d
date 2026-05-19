#include "../inc/cub3d.h"

int is_empty(char *line)
{
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || line[i] == '\r')
        i++;
    return (line[i] == '\0'); // Si llegamos al final, es que estaba "vacía"
}

int process_line(char *line, t_game *data, int *ids_found, char **file_content)
{
    t_type_id   type_id;

    if (is_empty(line))
        return (SUCCESS);
    type_id = find_type_id(line);
    if (type_id)
    {
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
    // Si no es vacío ni ID, es el mapa
    if (*ids_found < 6)
    {
        data->error_msg = "Error: Invalid ID or missing elements before map";
        return (ERROR);
    }
    if (type_id == ID_ERROR)
    {
        if (validate_identifiers(data) == ERROR) 
            return (ERROR);
        if (extract_map(data, file_content) == ERROR) // Le pasamos dirección de la linea actual
            return (ERROR);
        return (MAP_DONE); //! ¿Que pasa si hay más lineas despues del mapa? Gestionarlo
    }
    return (SUCCESS);
}

//! Revisar que esta funcion retorne bien cuando falla
int fill_data(char **file_content, t_game *data)
{
    int i;
    int ids_found;
    int status;

    i = 0;
    ids_found = 0;
    while (file_content[i])
    {
        //! Revisar si deberia leer más lineas despues de terminar con el mapa
        status = process_line(file_content[i], data, &ids_found, &file_content[i]);
        if (status == ERROR || status == MAP_DONE)
            break ;
        i++;
    }
    if (status == MAP_DONE && validate_map(data) == ERROR)
        return (ERROR);
    return (SUCCESS);
}

void synchronize_player(t_game *data)
{
    //! Seria una buena practica poner a 0 el resto en cada if (aunque lo haga en init)
    if (data->map.player_dir == 'N')
    {
        data->player.dir_y = -1.0;
        data->player.plane_x = 0.66;
    }
    else if (data->map.player_dir == 'S')
    {
        data->player.dir_y = 1.0;
        data->player.plane_x = -0.66;
    }
    else if (data->map.player_dir == 'E')
    {
        data->player.dir_x = 1.0;
        data->player.plane_y = 0.66;
    }
    else if (data->map.player_dir == 'W')
    {
        data->player.dir_x = -1.0;
        data->player.plane_y = -0.66;
    }
    data->player.pos_x = (double)data->map.player_x + 0.5;
    data->player.pos_y = (double)data->map.player_y + 0.5;
}


int parse(t_game *data, char *file)
{
    char        **file_content;

    file_content = file_to_array(data, file);
    if (!file_content)
        return (ERROR);
    
    if (fill_data(file_content, data) == ERROR)
    {
        free_array(file_content);
        return (ERROR);
    }
    synchronize_player(data);
    
    //print_data(data);

    free_array(file_content);
    return (SUCCESS);
}