#include "../inc/cub3d.h"

void    free_all(t_game *data)
{
    (void)data;
}

void    free_array(char **array)
{
    int i;

    if (!array)
		return ;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}