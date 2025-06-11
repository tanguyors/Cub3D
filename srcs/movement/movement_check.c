#include "cub3d.h"

int	check_movement(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x < 0 || map_x >= game->map_width || map_y < 0
		|| map_y >= game->map_height)
		return (0);
	if (game->map[map_y][map_x] == '1')
		return (0);
	return (1);
}
