#include "cub3d.h"

int	check_horizontal_borders(t_map *map)
{
	int	j;

	j = 0;
	while (j < map->width)
	{
		if (is_space_or_player(map->grid[0][j])
			|| is_space_or_player(map->grid[map->height - 1][j]))
			return (0);
		j++;
	}
	return (1);
}

int	check_vertical_borders(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (is_space_or_player(map->grid[i][0])
			|| is_space_or_player(map->grid[i][map->width - 1]))
			return (0);
		i++;
	}
	return (1);
}

int	check_spaces_around(t_map *map)
{
	int	i;
	int	j;

	i = 1;
	while (i < map->height - 1)
	{
		j = 1;
		while (j < map->width - 1)
		{
			if (is_space_or_player(map->grid[i][j]))
			{
				if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' '
					|| map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_borders(t_map *map)
{
	if (!check_horizontal_borders(map) || !check_vertical_borders(map)
		|| !check_spaces_around(map))
		return (0);
	return (1);
}