#include "../inc/cub3d.h"
/*
int is_empty(char *line)
{
    if (line[0] == '\0' || line[0] == '\n')
        return (1);
    return (0);
}
*/
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

    printf("Hola2\n");
    (void)file_content;
    if (is_empty(line))
        return (SUCCESS);
    printf("Hola\n");
    type_id = find_type_id(line);
    if (type_id)
    {
        printf("Hola\n");
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
        if (extract_map(data, &line) == ERROR) // Le pasamos dirección de la linea actual
            return (ERROR);
        return (SUCCESS); //! ¿Que pasa si hay más lineas despues del mapa? Gestionarlo
    }
    return (SUCCESS);
}

//! Revisar que esta funcion retorne bien cuando falla
int fill_data(char **file_content, t_game *data)
{
    int i;
    int ids_found;

    i = 0;
    ids_found = 0;
    while (file_content[i])
    {
        printf("AAA\n");
        //! Revisar si deberia leer más lineas despues de terminar con el mapa
        if (process_line(file_content[i], data, &ids_found, file_content) == ERROR)
            break ;
        i++;
    }
    if (validate_map(data) == ERROR)
        return (ERROR);
    return (SUCCESS);
}

int parse(t_game *data, char *file)
{
    char        **file_content;

    file_content = file_to_array(data, file);
    if (!file_content)
        return (ERROR);
    
    if (fill_data(file_content, data) == ERROR)
        return (ERROR);
    
    print_data(data);

    free_array(file_content);
    return (SUCCESS);
}