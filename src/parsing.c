





#include "cub.h"

int	get_text_path(game_s *game, char *filepath);

int process_create_map(game_s *game, char *file)
{
    // 1 -> recuperer orientation joueur et remplir la structure textures
    //  . return -1 error
    int y;
    printf("rentre dans le create map\n");
    read_maap(file, game);
    y = init_all_texture(game);
    printf("valeur de y :%d\n", y);
    if (y == -1) // gerer ici les free etc ..
        exit(1);
    y++;
    if (isclosed(game, y) == 0) // gerer ici les free etc ..
        exit(1);
     //if (isclosed_column(game, y) == 0) // reussir a faire fonctionner la fct qui permet de check
       // exit(1);
    // en colonne si c'est bien 1 le dernier et pas un 0

    if (init_pos_player(game, y) == -1) // gerer ici les free etc ..
        exit(1);
    printf("Map valide bravo \n");
    return (0);
}




int	parsing(game_s *game, char *filepath)
{
	ft_memset(game, 0, sizeof(game_s));
	ft_memset(game->texture.c_color, -1, 3 * sizeof(int));
	ft_memset(game->texture.f_color, -1, 3 * sizeof(int));
	if(get_text_path(game, filepath))
		return (free_textures(game), 1);

    printf("%s\n", game->texture.text_no);
	printf("%s\n", game->texture.text_so);
	printf("%s\n", game->texture.text_ea);
	printf("%s\n", game->texture.text_we);
	printf("%d %d %d\n", game->texture.f_color[0], game->texture.f_color[1], game->texture.f_color[2]);
	printf("%d %d %d\n", game->texture.c_color[0], game->texture.c_color[1], game->texture.c_color[2]);

	return (0);
}
