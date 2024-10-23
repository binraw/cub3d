#include "../headers/cub.h"

int	raycaster(game_s *game);

/* === ONLY FOR DEBUG === */

void	print_struct(game_s *game)
{
	// display map + textures
    printf("%s\n", game->texture.text_no);
	printf("%s\n", game->texture.text_so);
	printf("%s\n", game->texture.text_ea);
	printf("%s\n", game->texture.text_we);
	printf("%d %d %d\n", game->texture.f_color[0], game->texture.f_color[1], game->texture.f_color[2]);
	printf("%d %d %d\n\n\n", game->texture.c_color[0], game->texture.c_color[1], game->texture.c_color[2]);
	int i = 0;
	while(game->map_data.map[i])
		printf("%s\n", game->map_data.map[i++]);
	printf("map size == %zu\n", game->map_data.heigth);
	printf("player pos : x == %f : y == %f\n", game->plyr_data.pos_x, game->plyr_data.pos_y);
}

void	print_player(game_s *game)
{
	printf("PLAYER DATA :\n");
	printf("pos_y == %f : pos_x = %f\n", game->plyr_data.pos_y, game->plyr_data.pos_x);
	printf("dir_y == %f : dir_x = %f\n", game->plyr_data.dir_y, game->plyr_data.dir_x);
	printf("angle == %f\n\n", game->plyr_data.angle);
}

int	ft_perror(char *msg)
{
	write(2, "Error\n", 7);
	return ((int) write(2, msg, ft_strlen(msg)));
}

int main(int argc, char **argv)
{
    game_s game;

    (void)argc;
    if (argc != 2)
		return (ft_perror(USAGE), EXIT_FAILURE);
	if (parsing(&game, argv[1]))
		return (1);
	if (init_console(&game))
		return (free_map_data(&game), EXIT_FAILURE);
	print_player(&game);
	raycaster(&game);
	hook_management(&game);
	mlx_loop_hook(game.console.mlx_ptr, loop_hook, &game);
    mlx_loop(game.console.mlx_ptr);
	free_console(&game);
	free_map_data(&game);
	return (0);
}
