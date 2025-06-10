#include "cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

int	check_map_chars(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (!is_valid_char(game->map.grid[i][j]))
			{
				ft_printf("Invalid char '%c' (ASCII: %d) at [%d][%d]\n",
					game->map.grid[i][j], (int)game->map.grid[i][j], i, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	is_space_or_player(char c)
{
	if (c == '0' || c == 'W' || c == 'N' || c == 'S' || c == 'E')
		return (1);
	return (0);
}