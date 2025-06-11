#include "cub3d.h"

int	check_top_border(t_game *game)
{
	int	j;

	j = 0;
	while (j < game->map_width)
	{
		if (game->map[0][j] != '1' && game->map[0][j] != ' ')
		{
			ft_printf("Error: Invalid top border\n");
			return (0);
		}
		j++;
	}
	return (1);
}

int	check_bottom_border(t_game *game)
{
	int	j;

	j = 0;
	while (j < game->map_width)
	{
		if (game->map[game->map_height - 1][j] != '1'
			&& game->map[game->map_height - 1][j] != ' ')
		{
			ft_printf("Error: Invalid bottom border\n");
			return (0);
		}
		j++;
	}
	return (1);
}

int	check_left_border(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] != '1' && game->map[i][0] != ' ')
		{
			ft_printf("Error: Invalid left border\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_right_border(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][game->map_width - 1] != '1'
			&& game->map[i][game->map_width - 1] != ' ')
		{
			ft_printf("Error: Invalid right border\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_map_borders(t_game *game)
{
	if (!check_top_border(game))
		return (0);
	if (!check_bottom_border(game))
		return (0);
	if (!check_left_border(game))
		return (0);
	if (!check_right_border(game))
		return (0);
	return (1);
}