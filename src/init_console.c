#include "../headers/cub.h"

static int	loop_hook(game_s *game)
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
	return (0);
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
	return (0);
}