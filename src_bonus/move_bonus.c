/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:29:24 by fberthou          #+#    #+#             */
/*   Updated: 2024/11/13 08:29:28 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static inline int	move(game_s *game, double move_x, double move_y)
{
    int		map_grid_y;
	int		map_grid_x;
	double	new_x;
	double	new_y;

    new_x = game->plyr_data.pos_x + move_x * 1.2;
	new_y = game->plyr_data.pos_y + move_y * 1.2;
	map_grid_x = (int) floor((double)new_x / TILE_S);
	map_grid_y = (int) floor((double)new_y / TILE_S);
	if (game->map_data.map[map_grid_y][map_grid_x] != '1' && \
        game->map_data.map[map_grid_y][map_grid_x] != ' ')
	{
		game->plyr_data.pos_x = game->plyr_data.pos_x + move_x;
		game->plyr_data.pos_y = game->plyr_data.pos_y + move_y;
        return (0);
	}
    return (1);
}

void	rot_player(game_s *game, int is_mouse)
{
    static const double    m_rot_speed = (ROT_SPEED * 0.8);

    if (is_mouse == 1)
        game->plyr_data.angle -= m_rot_speed;
    else if (game->plyr_data.rotate_l == 1)
        game->plyr_data.angle -= ROT_SPEED;
    if (is_mouse == 2)
        game->plyr_data.angle += m_rot_speed;
    else if (game->plyr_data.rotate_r)
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
    if (game->plyr_data.rotate_l || game->plyr_data.rotate_r || \
                                        game->plyr_data.rotate_m)
        rot_player(game, 0);
    if (game->plyr_data.move_up)
        return (move(game, cos(game->plyr_data.angle) * MOV_SPEED, \
                            sin(game->plyr_data.angle) * MOV_SPEED));
    if (game->plyr_data.move_down)
        return (move(game, -cos(game->plyr_data.angle) * MOV_SPEED, \
                            -sin(game->plyr_data.angle) * MOV_SPEED));
    if (game->plyr_data.move_left)
        return (move(game, sin(game->plyr_data.angle) * MOV_SPEED, \
                            -cos(game->plyr_data.angle) * MOV_SPEED));
    if (game->plyr_data.move_right)
        return (move(game, -sin(game->plyr_data.angle) * MOV_SPEED, \
                            cos(game->plyr_data.angle) * MOV_SPEED));
    return (0);
}
