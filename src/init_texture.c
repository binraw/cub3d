






#include "cub.h"

static bool	not_dup_is_digit(char **buff, int *colors)
{
	size_t	i;
	size_t	y;

	y = 0;
	i = 0;
    while (i < 3)
    {
        if (colors[i] != -1)
            return (ft_perror("A color is duplicated in file\n"), false);
        i++;
    }
    i = 0;
	while (buff[i])
	{
		while (buff[i][y] && buff[i][y] != '\n')
		{
			if (ft_isdigit(buff[i][y]) == 0)
				return (ft_perror("Bad RGB value in file\n"), false);
			y++;
		}
		y = 0;
		i++;
	}
	return (true);
}

static int	fill_colors(char *buffer, int *colors)
{
	char	**tmp;
	size_t	i;

	i = 1;
	while(buffer[i] && buffer[i] == ' ')
		i++;
	tmp = ft_split(&buffer[i], ',');
	if (!tmp)
		return (ft_perror("crash malloc in fill_color\n"));
	if (not_dup_is_digit(tmp, colors) == false)
		return (free_ptrtab(tmp), 1);
	i = -1;
	while (tmp[++i] && i < 3 && tmp[i][0])
	{
		colors[i] = ft_atoi(tmp[i]);
		if (colors[i] < 0 || colors[i] > 255)
			return (free_ptrtab(tmp), \
                    ft_perror("Invalid colors value in file\n"));
	}
	while (tmp[i])
		i++;

	if (i != 3)
		return (free_ptrtab(tmp), ft_perror("Invalid color format in file\n"));
	return (free_ptrtab(tmp), 0);
}

static int	fill_direction(char *buff_f, char **buff_t, game_s *game)
{
	size_t	i;
	int		fd;

	i = 2;
	while (buff_f[i] && buff_f[i] == ' ')
		i++;
    if (*buff_t != NULL)
        return (ft_perror("One direction field is duplicated\n"));
	*buff_t = ft_substr(buff_f, i, ft_strlen(buff_f) - i + 1);
	if (!*buff_t)
		return (ft_perror("crash malloc in fill_direction\n"));
    game->texture.all_text += 1;
	return (0);
}

static int	line_analysis(game_s *game, char *buffer)
{
	if (buffer[0] == 'N' && buffer[1] == 'O')
		return (fill_direction(buffer, &game->texture.text_no, game));
	else if (buffer[0] == 'S' && buffer[1] == 'O')
		return (fill_direction(buffer, &game->texture.text_so, game));
	else if (buffer[0] == 'E' && buffer[1] == 'A')
		return (fill_direction(buffer, &game->texture.text_ea, game));
	else if (buffer[0] == 'W' && buffer[1] == 'E')
		return (fill_direction(buffer, &game->texture.text_we, game));
	else if (buffer[0] == 'F')
    {
        game->texture.all_text += 1;
		return (fill_colors(buffer, game->texture.f_color));
    }
	else if (buffer[0] == 'C')
    {
        game->texture.all_text += 1;
		return (fill_colors(buffer, game->texture.c_color));
    }
	return (0);
}

int	get_text_path(game_s *game, char *filepath)
{
	char		*buffer;
    const int   fd = open(filepath, O_RDONLY);

	if (fd < 0)
		return (ft_perror("file can't be open\n"));
	buffer = "buf";
	while (buffer != NULL && game->texture.all_text != 6)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		if (buffer[0] == '\n' || buffer[0] == '\0')
			;
		else if (line_analysis(game, buffer))
			return (close(fd), free(buffer), 1);
		free(buffer);
	}
	if (game->texture.all_text != 6)
    {
        printf("%d\n", game->texture.all_text);
		return (close(fd), ft_perror("Textures data are invalid\n"));
    }
    if (close(fd) == -1)
        return (ft_perror("Fd closure failed in get_text_path\n"));
	return (0);
}
