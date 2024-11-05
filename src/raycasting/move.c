#include "cub.h"

static int	move(game_s *game, double move_x, double move_y)
{
    int		map_grid_y;
	int		map_grid_x;
	double	new_x;
	double	new_y;

    new_x = game->plyr_data.pos_x + move_x;
	new_y = game->plyr_data.pos_y + move_y;
	map_grid_x = (int) floor((double)new_x / TILE_S);
	map_grid_y = (int) floor((double)new_y / TILE_S);
	if (game->map_data.map[map_grid_y][map_grid_x] != '1' && \
        game->map_data.map[map_grid_y][map_grid_x] != ' ')
	{
		game->plyr_data.pos_x = new_x;
		game->plyr_data.pos_y = new_y;
        return (0);
	}
    return (1);
}

static void	rotate_player(game_s *game)
{
    if (game->plyr_data.rotate_l)
        game->plyr_data.angle -= ROT_SPEED;
    if (game->plyr_data.rotate_r)
        game->plyr_data.angle += ROT_SPEED;
    if (game->plyr_data.angle < 0)
        game->plyr_data.angle += M_PI * 2;
    if (game->plyr_data.angle > M_PI * 2)
        game->plyr_data.angle -= M_PI * 2;
    game->plyr_data.dir_x = cos(game->plyr_data.angle);
    game->plyr_data.dir_y = sin(game->plyr_data.angle);
    game->plyr_data.plane_x = -game->plyr_data.dir_y * tan(FOV_2);
    game->plyr_data.plane_y = game->plyr_data.dir_x * tan(FOV_2);
}

int update_movement(game_s *game)
{
    if (game->plyr_data.rotate_l || game->plyr_data.rotate_r)
        rotate_player(game);
    else if (game->plyr_data.move_up)
        return (move(game, cos(game->plyr_data.angle) * MOV_SPEED, \
                            sin(game->plyr_data.angle) * MOV_SPEED));
    else if (game->plyr_data.move_down)
        return (move(game, -cos(game->plyr_data.angle) * MOV_SPEED, \
                            -sin(game->plyr_data.angle) * MOV_SPEED));
    else if (game->plyr_data.move_left)
        return (move(game, sin(game->plyr_data.angle) * MOV_SPEED, \
                            -cos(game->plyr_data.angle) * MOV_SPEED));
    else if (game->plyr_data.move_right)
        return (move(game, -sin(game->plyr_data.angle) * MOV_SPEED, \
                            cos(game->plyr_data.angle) * MOV_SPEED));
    return (0);
}
