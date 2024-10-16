






#include "cub.h"

int	close_win(game_s *game, int key_code)
{
	(void) key_code;
	return (mlx_loop_end(game->console.mlx_ptr));
}

int key_up(int code, game_s *game)
{
	if (code == XK_Escape)
		return (mlx_loop_end(game->console.mlx_ptr));
	else if (code == 'w')
		game->plyr_data.move_up = 0;
	else if (code == 's')
		game->plyr_data.move_down = 0;
	else if (code == 'a')
		game->plyr_data.move_left = 0;
	else if (code == 'd')
		game->plyr_data.move_right = 0;
	else if (code == 65361)
		game->plyr_data.rotate_l = 0;
	else if (code == 65363)
		game->plyr_data.rotate_r = 0;
	return (0);
}

int key_down(int code, game_s *game)
{
	if (code == XK_Escape)
		return (mlx_loop_end(game->console.mlx_ptr));
	else if (code == 'w')
		game->plyr_data.move_up = 1;
	else if (code == 's')
		game->plyr_data.move_down = 1;
	else if (code == 'a')
		game->plyr_data.move_left = 1;
	else if (code == 'd')
		game->plyr_data.move_right = 1;
	else if (code == 65361)
		game->plyr_data.rotate_l = 1;
	else if (code == 65363)
		game->plyr_data.rotate_r = 1;
	return (0);
}

int	loop_hook(game_s *game)
{
	if (game->plyr_data.move_down)
        game->plyr_data.pos_y += game->plyr_data.mov_speed;
	if (game->plyr_data.move_up)
        game->plyr_data.pos_y -= game->plyr_data.mov_speed;
	if (game->plyr_data.move_left)
        game->plyr_data.pos_x -= game->plyr_data.mov_speed;
	if (game->plyr_data.move_right)
        game->plyr_data.pos_x += game->plyr_data.mov_speed;
    if (game->plyr_data.rotate_l)
        game->plyr_data.orientation -= game->plyr_data.rot_speed;
    if (game->plyr_data.rotate_r)
        game->plyr_data.orientation += game->plyr_data.rot_speed;
    if (game->plyr_data.rotate_l || game->plyr_data.rotate_r)
    {
        game->plyr_data.pos_x = cos(game->plyr_data.orientation);
        game->plyr_data.pos_y = sin(game->plyr_data.orientation);
    }
	return (0)
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
	ft_memset(game, 0, sizeof(game_s));
	game->console.mlx_ptr = mlx_init();
	if (!game->console.mlx_ptr)
		return (ft_perror("mlx alloc failed\n"));
	game->console.win_ptr = mlx_new_window(game->console.mlx_ptr, \
											WIN_W, WIN_H, "Cub3d");
	if (!game->console.win_ptr)
	{
		mlx_destroy_display(game->console.mlx_ptr);
		return (free(game->console.mlx_ptr), ft_perror("win alloc failed\n"));
	}
	hook_management(game);
	mlx_loop_hook(game->console.mlx_ptr, loop_hook, game);
	// mlx_loop(game->console.mlx_ptr);
	return (0);
}