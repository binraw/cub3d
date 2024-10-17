#include "../headers/cub.h"

int	raycaster(game_s *game);


int	ft_perror(char *msg)
{
	return (write(2, msg, ft_strlen(msg)));
}





int main(int argc, char **argv)
{
    game_s game;

	//(void)argv;
    (void)argc;
    if (argc != 2)
		return (ft_perror(USAGE), EXIT_FAILURE);
	if (init_console(&game))
		return (EXIT_FAILURE);
    game.file = NULL;
	process_create_map(&game, argv[1]);
	// process_create_map(&game, argv[1]);


	// init provisoire pour raycasting
	// game.map_data.map = ft_calloc(5, sizeof(char *));
	// game.map_data.map[0] = ft_strdup("1111111111111111111111111"); 
	// game.map_data.map[1] = ft_strdup("1000000000110000000000001");
	// game.map_data.map[2] = ft_strdup("1011000001110000000000001");
	// game.map_data.map[3] = ft_strdup("100100000000000000000N001");
	// game.map_data.map[4] = ft_strdup("1111111111111111111111111");
	// game.map_data.heigth = 5; // == nombre de lignes de la map
	// game.map_data.width = ft_strlen(game.map_data.map[4]); // == plus longue ligne de la map
	// game.texture.f_color = 0x0000FF;
	// game.texture.c_color = 0xFF0000;


	raycaster(&game);

    mlx_loop(game.console.mlx_ptr);
	for(int i = 0; i<5; i++){
		free(game.map_data.map[i]);
	}
	free(game.map_data.map);
	free_console(&game);
	return (0);
}




