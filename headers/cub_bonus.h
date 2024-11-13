
#ifndef CUB_BONUS_H
# define CUB_BONUS_H

    /* === INCLUDES === */

    # include "libft.h"
    # include "get_next_line.h"
    # include "mlx.h"
    # include "mlx_int.h"
    # include <sys/stat.h>
    # include <stdbool.h>
    # include <stdlib.h>
    # include <stdio.h>
    # include <fcntl.h>
    # include <math.h>

    /* ==== STRUCTURES ==== */

    typedef struct console
    {
		void	*mlx_ptr;
		void	*win_ptr;
    } console_s;

	typedef struct texture
	{
		char	*text_no;
		char	*text_so;
		char	*text_we;
		char	*text_ea;
		int		f_color[3];
		int		c_color[3];
		int     all_text;
	} texture_s ;

	typedef struct ray
	{
		double	angle;
		int		pos_x;
		int		pos_y;
		double	dir_x;
		double	dir_y;
		double	delta_x;
		double	delta_y;
		int		step_x;
		int		step_y;
		double	side_x;
		double	side_y;
		double	wall_dist;
		bool	colision_side;
	} ray_s;

    typedef struct player
    {
		bool	write;
		double	pos_x;
		double	pos_y;
		double	dir_x;
		double	dir_y;
		double	plane_x;
		double	plane_y;
		double	camera_x;
		double	angle;
		bool	move_up;
		bool	move_down;
		bool	move_right;
		bool	move_left;
		bool	rotate_r;
		bool	rotate_l;
        int     rotate_m;
    } player_s;

	typedef struct map
	{
        char	**map;
		size_t	width;
		size_t	heigth;
	} map_s;

	typedef struct img
	{
		int     height;
		int     width;
		void    *img_ptr;
        char    *data;
		int		bpp;
		int		s_line;
		int		endian;
	}	img_s;

	typedef struct draw
	{
		int	wall_h;
		int	wall_t;
		int	wall_b;
		int	floor_c;
		int	ceiling_c;
	}	draw_s;

    typedef struct game_s
    {
		console_s	console;
		texture_s	texture;
		map_s		map_data;
		player_s	plyr_data;
		draw_s		draw;
		ray_s		ray_data;
		img_s		img_data[4];
		img_s		img;
    } game_s;

/* ==== CONSTANTES ==== */

    // ERROR MESSAGES //
	# define USAGE	        "Need one filepath as argument\n"
    # define E_FILE_FORMAT	"A file format error is detected\n"
    # define E_MULTIPLAY    "Multiple player definition is forbidden\n"
    # define E_INVALID_CHAR "Invalid char in the map\n"
    # define E_EMPTYLINE    "Empty line in the map description is forbidden\n"

    // COLOR //
    # define RED        0Xc70404
    // WINDOW WIDTH HEIGTH //
	# define WIN_W		700
	# define WIN_H		700

    // MLX PTR ACCESS //
	# define MLX_PTR	game->console.mlx_ptr
	# define WIN_PTR	game->console.win_ptr

	// PLAYER ORIENTATION //
	# define ANGLE_N	4.71238898		// == (3 * M_PI) / 2
	# define ANGLE_S	M_PI_2
	# define ANGLE_E	0
	# define ANGLE_W	M_PI

    // FIELD OF VIEW //
	# define ANGLE_FOV	1.047197551		// == M_PI / 3 == 60 degrees
	# define FOV_2		0.5235987756	// == M_PI / 6 == 30 degrees

    // MOVES SPEED //
	# define ROT_SPEED	0.03
	# define MOV_SPEED	3
	# define TILE_S		64

    // MINIMAP //
    #define M_TILE_S    10

/* === PROTOTYPES === */

	/* === main.c === */
	int		ft_perror(char *msg);

	/* === init_console.c === */
	int		init_console(game_s *game);
	void	hook_management(game_s *game);
    int	init_console_mlx(game_s *game);

	/* === free_memory.c === */
	void	free_console(game_s *game);
	void	free_textures(game_s *game);
	void	free_ptrtab(char **tab);
	void	free_ptrtab_map(char **tab, size_t len);
	void	free_map_data(game_s *game);
	int		destroy_all(game_s *game);

	/* === parsing.c === */
	int		parsing(game_s *game, char *filepath);

	/* === parsing_utils.c === */
	bool	is_valid_char(char c);
	bool	is_empty_line(char *buffer);
	bool	is_player(char c);
	char	**duplicate_map(char **src, size_t nb_ptr);
	int		alloc_tab(game_s *game, bool first_alloc);
    static void	init_data_angle(game_s *game, float angle, int x, int y);

	/* === init_map.c === */
	int		get_map(game_s *game, int fd);

	/* === valid_map.c === */
	int		check_map_validity(game_s *game);

	/* === init_texture.c === */
	int		get_textures(game_s *game, int fd);

	/* === texture.c === */
	int    load_texture(game_s *game);
    size_t	ft_strlen_texture(const char *str);
    
	/* === raycaster.c === */
	int		loop_hook(game_s *game);

	/* === utils_raycaster.c === */
	void	init_ray(ray_s *ray, game_s *game, int nb_ray);
    int	define_index(game_s *game, int nb, int index);
    int	utils_color(game_s *game, ray_s *ray, int nb, int y_start);

	/* === move.c === */
	int		update_movement(game_s *game);

	/* === draw.c === */
	void	draw_column(game_s *game, ray_s *ray, int column_index	);
	void    my_mlx_pixel_put(img_s *data, int x, int y, int color);

    /* === mini_map.c === */
    void    print_minimap(game_s *game, ray_s *ray);

    /***=== BONUS FILES ===***/
    /* === move_bonus.c === */
    void	rotate_player(game_s *game, int is_mouse);

    /* === hook_utils_bonus.c === */
    bool	is_movement(game_s *game);
    int		close_win(game_s *game, int key_code);
    int		change_mouse_pos(game_s *game, int x, int y);

#endif