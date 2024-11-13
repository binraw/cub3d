

#include "cub.h"

static int	key_up(int code, game_s *game)
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

static int	key_down(int code, game_s *game)
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

static int	mouse_hook(int x, int y, game_s *game)
{
	static int  old_x = WIN_W >> 1;
    static int  count;

	change_mouse_pos(game, x, y);
	if (x >= old_x - 5 && x <= old_x + 5 && !count)
    {
        count = 1;
		return (0);
    }
    if ((x != old_x && !count) || x == old_x)
        return (0);
    if (x < old_x)
    {
	    game->plyr_data.rotate_m = 1;
		rot_player(game, 1);
    }
	else if (x > old_x)
    {
	    game->plyr_data.rotate_m = 2;
		rot_player(game, 2);
    }
	old_x = x;
	return (0);
}

void	hook_management(game_s *game)
{
	mlx_hook(game->console.win_ptr, DestroyNotify, StructureNotifyMask, \
														close_win, game);
    mlx_hook(game->console.win_ptr, KeyPress, KeyPressMask, key_down, game);
    mlx_hook(game->console.win_ptr, KeyRelease, KeyReleaseMask, key_up, game);
    mlx_hook(WIN_PTR, MotionNotify, PointerMotionMask, mouse_hook, game);
	return ;
}
