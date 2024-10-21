#include "../headers/cub.h"

int	raycaster(game_s *game);


int	ft_perror(char *msg)
{
	write(2, "Error\n", 7);
	return ((int) write(2, msg, ft_strlen(msg)));
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

		
	// raycaster(&game);
	hook_management(&game);
	mlx_loop_hook(game.console.mlx_ptr, loop_hook, &game);
	
	
    mlx_loop(game.console.mlx_ptr);
	// free_console(&game);
	free_map_data(&game);
	return (0);
}
