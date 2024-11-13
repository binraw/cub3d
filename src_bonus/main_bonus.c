/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:04:44 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/13 11:05:14 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	ft_perror(char *msg)
{
	write(2, "Error\n", 7);
	return ((int) write(2, msg, ft_strlen(msg)));
}

int	main(int argc, char **argv)
{
	game_s	game;

	(void)argc;
	if (argc != 2)
		return (ft_perror(USAGE), EXIT_FAILURE);
	if (parsing(&game, argv[1]))
		return (EXIT_FAILURE);
	if (init_console_mlx(&game))
		return (free_map_data(&game), EXIT_FAILURE);
	if (init_console(&game))
		return (free_map_data(&game), EXIT_FAILURE);
	load_texture(&game);
	hook_management(&game);
	mlx_loop_hook(game.console.mlx_ptr, loop_hook, &game);
	mlx_loop(game.console.mlx_ptr);
	destroy_all(&game);
	return (0);
}
