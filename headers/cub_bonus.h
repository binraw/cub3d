/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:05:05 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/27 16:34:47 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <sys/stat.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>

typedef struct console
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_console;

typedef struct texture
{
	char	*text_no;
	char	*text_so;
	char	*text_we;
	char	*text_ea;
	int		f_color[3];
	int		c_color[3];
	int		all_text;
}	t_texture;

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
}	t_ray;

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
	int		rotate_m;
}	t_player;

typedef struct map
{
	char	**map;
	size_t	width;
	size_t	heigth;
}	t_map;

typedef struct img
{
	int		height;
	int		width;
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		s_line;
	int		endian;
}	t_img_data;

typedef struct draw
{
	int	wall_h;
	int	wall_t;
	int	wall_b;
	int	floor_c;
	int	ceiling_c;
}	t_draw;

typedef struct t_game
{
	t_console	console;
	t_texture	texture;
	t_map		map_data;
	t_player	plyr_data;
	t_draw		draw;
	t_ray		ray_data;
	t_img_data	img_data[4];
	t_img_data	img;
}	t_game;

# define USAGE	        "Need one filepath as argument\n"
# define E_FILE_FORMAT	"A file format error is detected\n"
# define E_MULTIPLAY    "Multiple player definition is forbidden\n"
# define E_INVALID_CHAR "Invalid char in the map\n"
# define E_EMPTYLINE    "Empty line in the map description is forbidden\n"
# define RED        0Xc70404
# define WIN_W		700
# define WIN_H		700
# define ANGLE_N	4.71238898
# define ANGLE_S	M_PI_2
# define ANGLE_E	0
# define ANGLE_W	M_PI
# define ANGLE_FOV	1.047197551
# define FOV_2		0.5235987756
# define ROT_SPEED	0.03
# define MOV_SPEED	3
# define TILE_S		64
# define M_TILE_S    10

int		ft_perror(char *msg);
int		init_console(t_game *game);
void	hook_management(t_game *game);
int		init_console_mlx(t_game *game);
void	free_console(t_game *game);
void	free_textures(t_game *game);
void	free_map(char **tab, size_t len);
void	free_map_data(t_game *game);
int		destroy_all(t_game *game);
int		parsing(t_game *game, char *filepath);
bool	is_valid_char(char c);
bool	is_empty_line(char *buffer);
bool	is_player(char c);
char	**duplicate_map(char **src, size_t nb_ptr);
int		alloc_tab(t_game *game, bool first_alloc);
int		get_map(t_game *game, int fd);
int		check_map_validity(t_game *game);
int		get_textures(t_game *game, int fd);
int		load_texture(t_game *game);
size_t	ft_strlen_texture(const char *str);
int		loop_hook(t_game *game);
void	init_ray(t_ray *ray, t_game *game, int nb_ray);
int		define_index(t_game *game, int nb, int index);
int		utils_color(t_game *game, t_ray *ray, int nb, int y_start);
int		update_movement(t_game *game);
void	draw_column(t_game *game, t_ray *ray, int column_index	);
void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
void	print_minimap(t_game *game);
void	rotate_player(t_game *game, int is_mouse);
bool	is_movement(t_game *game);
int		close_win(t_game *game, int key_code);
int		change_mouse_pos(t_game *game, int x, int y);
void	destroy_bad_line(t_game *game, char	*buffer);
size_t	skip_spaces(char *buffer);
int		check_line_validity(char **map, size_t x_start, size_t x_end, size_t y);
int		define_texture_x(t_game *game, t_ray *ray, int nb);
int		check_extension_xpm(char *str);

#endif
