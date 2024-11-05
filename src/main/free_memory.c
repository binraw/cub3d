

#include "cub.h"

void	free_ptrtab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

void	free_textures(game_s *game)
{
	if (game->texture.text_no != NULL)
		free(game->texture.text_no);
	if (game->texture.text_so != NULL)
		free(game->texture.text_so);
	if (game->texture.text_we != NULL)
		free(game->texture.text_we);
	if (game->texture.text_ea != NULL)
		free(game->texture.text_ea);
	return ;
}

void	free_map_data(game_s *game)
{
	free_textures(game);
	free_ptrtab(game->map_data.map);
}

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
