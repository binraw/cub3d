int	rotate(game_s *game)
{
	double	old_x;

	old_x = game->plyr_data.pos_x;
	game->plyr_data.pos_x = old_x * cos(game->plyr_data.angle) - game->plyr_data.pos_y * sin(game->plyr_data.angle);
	game->plyr_data.pos_y = old_x * sin(game->plyr_data.angle) + game->plyr_data.pos_y * cos(game->plyr_data.angle);
	return (EXIT_SUCCESS);
}

int	move(game_s *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->plyr_data.pos_x + game->plyr_data.dir_x  * MOVE_SPEED;
	new_pos_y = game->plyr_data.pos_y + game->plyr_data.dir_y * MOVE_SPEED;
	if (new_pos_x < 0 || new_pos_x >= game->map_data.width || \
		new_pos_y < 0 || new_pos_y >= game->map_data.heigth || \
		game->map_data[(int)new_pos_y][(int)new_pos_x] == C_WALL)
	{
		return (EXIT_FAILURE);
	}
	game->plyr_data.pos_x = new_pos_x;
	game->plyr_data.pos_y = new_pos_y;
	return (EXIT_SUCCESS);
}
