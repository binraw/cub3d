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
	printf("=== PLAYER DATA ===\n");
	printf("pos_y == %f : pos_x = %f\n", game->plyr_data.pos_y, game->plyr_data.pos_x);
	// printf("dir_y == %f : dir_x = %f\n", game->plyr_data.dir_y, game->plyr_data.dir_x);
	// printf("angle == %f\n\n", game->plyr_data.angle);
}

void	print_ray(ray_s *ray)
{
    printf("=== RAY ===\n");
    // printf("r_angle == %f\n", ray->angle);
    // printf("r_col_side == %d\n", ray->colision_side);
    // printf("r_deltaX == %f\n", ray->delta_x);
    // printf("r_deltaY == %f\n", ray->delta_y);
    // printf("r_sideX == %f\n", ray->side_x);
    // printf("r_sideY == %f\n", ray->side_y);
    printf("r_posX == %d\n", (ray->pos_x * TILE_S));
    printf("r_posY == %d\n", (ray->pos_y * TILE_S));
    printf("wall_dist == %f\n", ray->wall_dist);
    // printf("r_dirX == %f\n", ray->dir_x);
    // printf("r_dirY == %f\n", ray->dir_y);
    printf("\n");
}

void    print_constante(game_s *game)
{
    printf("CONSTANTES\n");
    printf("WIN_W == %d\n", WIN_W);
    printf("WIN_H == %d\n", WIN_H);
    printf("\n");
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
		return (EXIT_FAILURE);
	if (init_console(&game))
		return (free_map_data(&game), EXIT_FAILURE);
	load_texture(&game); // rajouter pour init
	raycaster(&game);
	hook_management(&game);
	mlx_loop_hook(game.console.mlx_ptr, loop_hook, &game);
	mlx_hook(game.console.win_ptr, 17, 0, destroy_img, &game);
	mlx_loop(game.console.mlx_ptr);
	free_console(&game);
	free_map_data(&game);
	return (0);
}
