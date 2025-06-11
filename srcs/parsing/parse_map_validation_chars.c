#include "cub3d.h"

static int	validate_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

int	validate_map_chars(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (!validate_map_char(game->map[i][j]))
			{
				ft_printf("Error: Invalid character in map at (%d, %d): %c\n",
					i, j, game->map[i][j]);
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