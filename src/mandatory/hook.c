/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:01:37 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/26 16:13:54 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	close_win(t_game *game, int key_code)
{
	(void) key_code;
	return (mlx_loop_end(game->console.mlx_ptr));
}

static int	key_up(int code, t_game *game)
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

static int	key_down(int code, t_game *game)
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

void	hook_management(t_game *game)
{
	mlx_hook(game->console.win_ptr, DestroyNotify, StructureNotifyMask, \
														close_win, game);
	mlx_hook(game->console.win_ptr, KeyPress, KeyPressMask, key_down, game);
	mlx_hook(game->console.win_ptr, KeyRelease, KeyReleaseMask, key_up, game);
	return ;
}
