#include "cub3d.h"

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(-ROTATE_SPEED)
		- game->player.dir_y * sin(-ROTATE_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROTATE_SPEED) + game->player.dir_y
		* cos(-ROTATE_SPEED);
	game->player.plane_x = game->player.plane_x * cos(-ROTATE_SPEED)
		- game->player.plane_y * sin(-ROTATE_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROTATE_SPEED)
		+ game->player.plane_y * cos(-ROTATE_SPEED);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(ROTATE_SPEED)
		- game->player.dir_y * sin(ROTATE_SPEED);
	game->player.dir_y = old_dir_x * sin(ROTATE_SPEED) + game->player.dir_y
		* cos(ROTATE_SPEED);
	game->player.plane_x = game->player.plane_x * cos(ROTATE_SPEED)
		- game->player.plane_y * sin(ROTATE_SPEED);
	game->player.plane_y = old_plane_x * sin(ROTATE_SPEED)
		+ game->player.plane_y * cos(ROTATE_SPEED);
}
