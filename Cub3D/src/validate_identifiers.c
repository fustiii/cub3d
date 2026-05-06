#include "../inc/cub3d.h"

static int  has_extension(char *path, char *end)
{
    size_t      path_len;
    size_t      end_len;

    path_len = strlen(path);
    end_len = strlen(end);

    if (path_len < end_len)
        return (0);

    if (strcmp(&path[path_len - end_len], end) == 0)
        return (1);
    return (0);
}

static int  can_open_file(t_game *data, char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        if (errno == ENOENT)
        {
            data->error_msg = "Error: The file does not exist";
            return (0);
        }
        else if (errno == EACCES)
        {
            data->error_msg = "Error: You do not have read permissions";
            return (0);
        }
        else
        {
            data->error_msg = "Unexpected error";
            //printf("Unexpected error (%d): %s\n", errno, strerror(errno));
            return (0);
        }
    }
    close(fd);
    return (1);
}

int    validate_identifiers(t_game *data)
{
    int i;
    char *path[4];
    path[0] = data->no_path;
    path[1] = data->so_path;
    path[2] = data->we_path;
    path[3] = data->ea_path;
    i = 0;
    while (i < 4)
    {
        if (!has_extension(path[i], ".xml"))
        {
            data->error_msg = "Missing extension .xml";
            return (ERROR);
        }
        if (!can_open_file(data, path[i]))
            return (ERROR);
        i++;
    }
    return (SUCCESS);
}