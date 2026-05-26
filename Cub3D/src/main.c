#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
	t_game   data;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file.cub>\n", argv[0]);
		return EXIT_FAILURE;
	}
	init_data(&data);
	if (parse(&data, argv[1]) == ERROR)
		exit_error(&data);
	start_game_graphics(&data);
	free_all(&data);
	return(EXIT_SUCCESS);
}