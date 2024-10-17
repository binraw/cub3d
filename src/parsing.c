





#include "cub.h"

int	get_text_path(game_s *game, char *filepath, int fd);

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
	const int	fd = open(filepath, O_RDONLY);

	if (fd < 0)
		return (ft_perror("file can't be open\n"));
	ft_memset(game, 0, sizeof(game_s));
	ft_memset(game->texture.c_color, -1, 3 * sizeof(int));
	ft_memset(game->texture.f_color, -1, 3 * sizeof(int));
	if(get_text_path(game, filepath, fd))
		return (1);
	return (0);
}
