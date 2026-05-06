#include "../inc/cub3d.h"


int validate_map(t_game *data)
{
    (void)data;
    return (SUCCESS);
}

int extract_map(t_game *data, char **map)
{
    int i;

    i = 0;
    while(map[i] && !is_empty(map[i]))
        i++;
    data->map.rows = i;
    data->map.map = malloc(sizeof(char *) * (i + 1));
    if (!data->map.map)
        return (ERROR);
    i = 0;
    while(map[i] && !is_empty(map[i]))
    {
        data->map.map[i] = strdup(map[i]);
        i++;
    }
    data->map.map[i] = NULL;
    return (SUCCESS);
}