#include "../inc/cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// No sirve para quitar el salto de linea que heredamos de get_next_line
void trim_newline(char *str)
{
    int i;

    i = 0;
    if (!str)
        return;
    while (str[i])
    {
        // Si encontramos el salto de línea o retorno de carro, cortamos el string ahí
        if (str[i] == '\n' || str[i] == '\r')
        {
            str[i] = '\0';
            break;
        }
        i++;
    }
}