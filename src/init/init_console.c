#include "../headers/cub.h"

int	init_console(game_s *game)
{
    if (WIN_H == 0 || WIN_W == 0)
		return (ft_perror("Window width or heigth is set to 0\n"));
	game->console.mlx_ptr = mlx_init();
	if (!game->console.mlx_ptr)
		return (ft_perror("mlx alloc failed\n"));
	game->console.win_ptr = mlx_new_window(game->console.mlx_ptr, \
											WIN_W, WIN_H, "Cub3d");
	if (!game->console.win_ptr)
	{
		mlx_destroy_display(game->console.mlx_ptr);
		return (free(game->console.mlx_ptr), ft_perror("win alloc failed\n"));
	}
	memset(&game->img, 0, sizeof(img_s));
	game->img.img_ptr = mlx_new_image(game->console.mlx_ptr, WIN_W, WIN_H);
	if (!game->img.img_ptr) {
    fprintf(stderr, "Erreur lors de la création de l'image\n");
    return -1;
}
	game->img.data = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.s_line, &game->img.endian);
	if (!game->img.data) {
    fprintf(stderr, "Erreur lors de la création du buffer\n");
    return -1;
}
	return (0);
}
