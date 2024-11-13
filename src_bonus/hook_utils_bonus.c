/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:56:31 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/13 10:57:21 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	close_win(game_s *game, int key_code)
{
	(void) key_code;
	return (mlx_loop_end(game->console.mlx_ptr));
}

int	change_mouse_pos(game_s *game, int x, int y)
{
	if (x > WIN_W - 20)
	{
		x = 20;
		mlx_mouse_move(MLX_PTR, WIN_PTR, x, y);
	}
	if (x < 20)
	{
		x = WIN_W - 20;
		mlx_mouse_move(MLX_PTR, WIN_PTR, x, y);
	}
	return (x);
}

bool	is_movement(game_s *game)
{
	return (game->plyr_data.move_up || game->plyr_data.move_down || \
			game->plyr_data.move_left || game->plyr_data.move_right || \
			game->plyr_data.rotate_l || game->plyr_data.rotate_r || \
			game->plyr_data.rotate_m);
}
