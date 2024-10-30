#include "cub.h"


void    load_texture(game_s *game)
{
    ft_memset(game->img_data.width, -1, 4 * sizeof(int));
	ft_memset(game->img_data.height, -1, 4 * sizeof(int));
    init_texture_no(game);
    init_texture_so(game);
    init_texture_we(game);
    init_texture_ea(game);
}


void    init_texture_no(game_s *game)
{
    int width;
    int height;

    game->img_data.img_text_no = mlx_xpm_file_to_image(game->console.mlx_ptr, game->texture.text_no, &width, &height);
    if (!game->img_data.img_text_no) // probleme car \n dans le nom de la texture
    {
        fprintf(stderr, "Erreur : Échec du chargement de l'image %s\n", game->texture.text_no);
         return ; // free et exit le programme
    }
    game->img_data.width[0] = width;
    game->img_data.height[0] = height;
    printf("valeur de width no et sa height : %d %d\n", game->img_data.width[0], game->img_data.height[0]);
}

void    init_texture_so(game_s *game)
{
    int width;
    int height;

    game->img_data.img_text_so = mlx_xpm_file_to_image(game->console.mlx_ptr, game->texture.text_so, &width, &height);
    if (!game->img_data.img_text_so)
        return ; // free et exit le programme
    game->img_data.width[1] = width;
    game->img_data.height[1] = height;
}

void    init_texture_we(game_s *game)
{
    int width;
    int height;

    game->img_data.img_text_we = mlx_xpm_file_to_image(game->console.mlx_ptr, game->texture.text_we, &width, &height);
    if (!game->img_data.img_text_we)
        return ; // free et exit le programme
    game->img_data.width[2] = width;
    game->img_data.height[2] = height;
}

void    init_texture_ea(game_s *game)
{
    int width;
    int height;

    game->img_data.img_text_ea = mlx_xpm_file_to_image(game->console.mlx_ptr, game->texture.text_ea, &width, &height);
    if (!game->img_data.img_text_ea)
        return ; // free et exit le programme
    game->img_data.width[3] = width;
    game->img_data.height[3] = height;
}