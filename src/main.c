







#include "cub.h"

int	ft_perror(char *msg)
{
	return (write(2, msg, ft_strlen(msg)));
}

int main(int argc, char **argv)
{
    game_s game;

	(void)argv;
    (void)argc;
    if (argc != 2)
		return (ft_perror(USAGE), EXIT_FAILURE);
	if (init_console(&game))
		return (EXIT_FAILURE);
    game.map = NULL;
	process_create_map(&game, argv[1]);
    mlx_loop(game.console.mlx_ptr);
 
}