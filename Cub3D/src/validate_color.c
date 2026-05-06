#include "../inc/cub3d.h"

static int is_valid_byte(char *str)
{
    int value;

    // Convertimos la cadena a entero
    value = atoi(str); 
    
    if (value >= 0 && value <= 255)
        return (1);
    return (0);
}

static int is_str_digit(char *str)
{
    int i;

    i = 0;
    if (!str || str[i] == '\0')
        return (0);
    while (str[i])
    {
        if (str[i] == '\n' && str[i + 1] == '\0')
            break;
        printf("Digit-> %c\n", str[i]);
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

static int    count_char_ocurrences(char *token, char c)
{
    char    *ptr;
    int     commas;

    ptr = token;
    commas = 0;
    while ((ptr = strchr(ptr, c)) != NULL)
    {
        commas++;
        ptr++;
    }
    return (commas);
}

int validate_color(t_game *data, char **rgb, char *token)
{
    int i;

    if (count_char_ocurrences(token, ',') != 2)
    {
        data->error_msg = "Error: More than two commas";
        return (ERROR);
    }
    i = 0;
    while (rgb[i])
    {
        if (!is_str_digit(rgb[i]))
        {
            data->error_msg = "Error: Is not a digit";
            return (ERROR);
        }
        if (!is_valid_byte(rgb[i]))
        {
            data->error_msg = "Error: Is not a valid byte [0-255]";
            return (ERROR);
        }
        i++;
    }
    if (i != 3)
    {
        data->error_msg = "Error: There are either too many or too few color components";
        return (ERROR);
    }
    return (SUCCESS);
}