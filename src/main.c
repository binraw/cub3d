#include "cub.h"


int main(int argc, char **argv)
{
    game_s game;
    (void)argv;
    (void)argc;
    ft_bzero(game, sizeof(game_s));
    // if (argc != 2)
    //     return (EXIT_FAILURE);
    game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
		exit(EXIT_FAILURE);
    game.mlx_win = mlx_new_window(game.mlx_ptr, 500, 500, "Cub3dd");
    if (!game.mlx_win)
        return (-1); // ici free plus tard
    mlx_loop(game.mlx_ptr);
 
}