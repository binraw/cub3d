#include "../headers/cub.h"

static int	close_win(game_s *game, int key_code)
{
	(void) key_code;
	return (mlx_loop_end(game->console.mlx_ptr));
}

int key_up(int code, game_s *game)
{
	if (code == XK_Escape)
		return (mlx_loop_end(game->console.mlx_ptr));
	// else if (code == 'w')
	// 	map->player.move_up = 0;
	// else if (code == 's')
	// 	map->player.move_down = 0;
	// else if (code == 'a')
	// 	map->player.move_left = 0;
	// else if (code == 'd')
	// 	map->player.move_right = 0;
	// else if (code == 65361)
	// 	map->player.rotate_left = 0;
	// else if (code == 65363)
	// 	map->player.rotate_right = 0;
	return (0);
}

int key_down(int code, game_s *game)\
{
	if (code == XK_Escape)
		return (mlx_loop_end(game->console.mlx_ptr));
	// else if (code == 'w')
	// 	game->player.move_up = 1;
	// else if (code == 's')
	// 	game->player.move_down = 1;
	// else if (code == 'a')
	// 	game->player.move_left = 1;
	// else if (code == 'd')
	// 	game->player.move_right = 1;
	// else if (code == 65361)
	// 	game->player.rotate_left = 1;
	// else if (code == 65363)
	// 	game->player.rotate_right = 1;
	return (0);
}

void	hook_management(game_s *game)
{
	mlx_hook(game->console.win_ptr, DestroyNotify, StructureNotifyMask, \
														close_win, game);
    mlx_hook(game->console.win_ptr, KeyPress, KeyPressMask, key_down, game);
    mlx_hook(game->console.win_ptr, KeyRelease, KeyReleaseMask, key_up, game);
	return ;
}

int	init_console(game_s *game)
{
	game->console.mlx_ptr = mlx_init();
	if (!game->console.mlx_ptr)
		return (ft_perror("mlx alloc failed\n"));
	game->console.win_ptr = mlx_new_window(game->console.mlx_ptr, \
											1500, 1500, "Cub3d");
	if (!game->console.win_ptr)
	{
		mlx_destroy_display(game->console.mlx_ptr);
		return (free(game->console.mlx_ptr), ft_perror("win alloc failed\n"));
	}
	hook_management(game);
	// mlx_loop(game->console.mlx_ptr);
	return (0);
}