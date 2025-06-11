#include "cub3d.h"

static int	handle_player_found(t_game *game, int x, int y, char c,
		int *player_count)
{
	if (*player_count > 0)
	{
		ft_putstr_fd("Error\nMultiple player start positions\n", 2);
		return (0);
	}
	game->player_pos_x = x + 0.5;
	game->player_pos_y = y + 0.5;
	game->player_dir = c;
	(*player_count)++;
	return (1);
}

static int	check_player_count(int player_count)
{
	if (player_count == 0)
	{
		ft_putstr_fd("Error\nNo player start position found\n", 2);
		return (0);
	}
	return (1);
}

int	parse_player_position(t_game *game)
{
	int	player_count;
	int	x;
	int	y;

	player_count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				if (!handle_player_found(game, x, y, game->map[y][x],
						&player_count))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (check_player_count(player_count));
}
