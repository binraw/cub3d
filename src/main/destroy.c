/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:01:24 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/12 08:01:25 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_console(game_s *game)
{
	mlx_destroy_window(game->console.mlx_ptr, game->console.win_ptr);
	mlx_destroy_display(game->console.mlx_ptr);
	free(game->console.mlx_ptr);
	return ;
}

int	destroy_all(game_s *game)
{
	if (game->img_data[0].img_ptr)
		mlx_destroy_image(game->console.mlx_ptr, game->img_data[0].img_ptr);
	if (game->img_data[1].img_ptr)
		mlx_destroy_image(game->console.mlx_ptr, game->img_data[1].img_ptr);
	if (game->img_data[2].img_ptr)
		mlx_destroy_image(game->console.mlx_ptr, game->img_data[2].img_ptr);
	if (game->img_data[3].img_ptr)
		mlx_destroy_image(game->console.mlx_ptr, game->img_data[3].img_ptr);
	free_map_data(game);
	free_console(game);
	exit(EXIT_SUCCESS);
	return (0);
}
