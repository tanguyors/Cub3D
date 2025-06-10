#include "cub3d.h"

int	check_collision(t_game *game, double new_x, double new_y)
{
	t_point	points[4] = {{new_x - PLAYER_RADIUS, new_y - PLAYER_RADIUS}, {new_x
			+ PLAYER_RADIUS, new_y - PLAYER_RADIUS}, {new_x - PLAYER_RADIUS,
			new_y + PLAYER_RADIUS}, {new_x + PLAYER_RADIUS, new_y
			+ PLAYER_RADIUS}};
	int		grid_x;
	int		grid_y;

	for (int i = 0; i < 4; i++)
	{
		grid_x = (int)points[i].x;
		grid_y = (int)points[i].y;
		if (grid_x < 0 || grid_x >= game->map.width || grid_y < 0
			|| grid_y >= game->map.height)
			return (1);
		if (game->map.grid[grid_y][grid_x] == '1')
			return (1);
	}
	return (0);
}
