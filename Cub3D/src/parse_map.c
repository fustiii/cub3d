#include "../inc/cub3d.h"

static int  assign_player_data(t_game *data, int y, int x)
{
    char    pos;

    pos = data->map.map[y][x];
    if (pos == 'N' || pos == 'S' || pos == 'E' || pos == 'W')
    {
        if (data->map.player_y != -1)
            return (ERROR);
        data->map.player_y = y;
        if (data->map.player_x != -1)
            return (ERROR);
        data->map.player_x = x;
        if (data->map.player_dir != -1)
            return (ERROR);
        data->map.player_dir = pos;
    }
    return (SUCCESS);
}

static int  allowed_character(char pos)
{
    int is_allowed;

    is_allowed = 0;
    if (pos == '0')
        is_allowed = 1;
    if (pos == '1')
        is_allowed = 1;
    if (pos == 'N')
        is_allowed = 1;
    if (pos == 'S')
        is_allowed = 1;
    if (pos == 'E')
        is_allowed = 1;
    if (pos == 'W')
        is_allowed = 1;
    return (is_allowed);
}

//! Refactorizar función
int  validate_map(t_game *data)
{
    int     y;
    int     x;

    y = 0;
    while(data->map.map[y])
    {
        x = 0;
        while(data->map.map[y][x])
        {
            if (!allowed_character(data->map.map[y][x]))
            {
                data->error_msg = "Error: Invalid character in map";
                return (ERROR);
            }
            if (assign_player_data(data, y, x) == ERROR)
            {
                data->error_msg = "Error: Map has more than one player";
                return (ERROR);
            }
            x++;
        }
        y++;
    }
    if (data->map.player_y == -1)
    {
        data->error_msg = "Error: No player position found";
        return (ERROR);
    }
    if (flood_fill(data) == ERROR)
    {
        data->error_msg = "Error: Map is not enclosed by walls";
        return (ERROR);
    }
    return (SUCCESS);
}

int extract_map(t_game *data, char **map)
{
    int i;
    int j;

    i = 0;
    trim_newline(map[0]);
    data->map.cols = ft_strlen(map[i]);
    while(map[i] && !is_empty(map[i]))
        i++;
    data->map.rows = i;
    data->map.map = malloc(sizeof(char *) * (i + 1));
    if (!data->map.map)
        return (ERROR);
    i = 0;
    while(map[i] && !is_empty(map[i]))
    {
        trim_newline(map[i]);
        j = 0;
        while(is_space(map[i][j]))
            j++;
        data->map.map[i] = ft_strdup(&map[i][j]);
        i++;
    }
    data->map.map[i] = NULL;
    return (SUCCESS);
}