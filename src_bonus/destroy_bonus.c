/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:23:14 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/13 16:27:44 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	free_console(t_game *game)
{
	mlx_destroy_window(game->console.mlx_ptr, game->console.win_ptr);
	mlx_destroy_display(game->console.mlx_ptr);
	free(game->console.mlx_ptr);
	return ;
}

int	destroy_all(t_game *game)
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

void	destroy_bad_line(t_game *game, char	*buffer)
{
	if (game->map_data.map)
		free_map(game->map_data.map, game->map_data.heigth);
	free(buffer);
}
