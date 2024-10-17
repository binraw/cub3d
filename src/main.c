







#include "cub.h"

int	raycaster(game_s *game);


int	ft_perror(char *msg)
{
	write(2, "Error\n", 7);
	return (write(2, msg, ft_strlen(msg)));
}

int main(int argc, char **argv)
{
    game_s game;

	(void)argv;
    (void)argc;
    if (argc != 2)
		return (ft_perror(USAGE), EXIT_FAILURE);
	if (parsing(&game, argv[1]))
		return (1);
	if (init_console(&game))
		return (EXIT_FAILURE);
	// process_create_map(&game, argv[1]);


	// raycaster(&game);

    mlx_loop(game.console.mlx_ptr);
	free_console(&game);
	free_textures(&game);
	return (0);
}




