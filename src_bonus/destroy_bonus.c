/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:23:14 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/13 13:30:19 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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
	if (game->img.img_ptr)
		mlx_destroy_image(game->console.mlx_ptr, game->img.img_ptr);
	free_map_data(game);
	free_console(game);
	exit(EXIT_SUCCESS);
	return (0);
}

void	destroy_bad_line(game_s *game, char	*buffer)
{
	if (game->map_data.map)
		free_ptrtab(game->map_data.map);
	free(buffer);
}
