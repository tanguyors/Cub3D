#include "cub3d.h"

/* Check collision */
int	check_collision(t_game *game, double new_x, double new_y)
{
	t_point	points[4] = {{new_x - PLAYER_RADIUS, new_y - PLAYER_RADIUS}, {new_x
			+ PLAYER_RADIUS, new_y - PLAYER_RADIUS}, {new_x - PLAYER_RADIUS,
			new_y + PLAYER_RADIUS}, {new_x + PLAYER_RADIUS, new_y
			+ PLAYER_RADIUS}};
	int		grid_x;
	int		grid_y;

	// Check 4 points around player (combat corner clipping)
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

/* Mouvement vers l'avant */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	if (!check_collision(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!check_collision(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}
/* Mouvement vers l'arrière */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	if (!check_collision(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!check_collision(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/* Mouvement latéral gauche */
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_y * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_x * MOVE_SPEED;
	if (!check_collision(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!check_collision(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/* Mouvement latéral droit */
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_y * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_x * MOVE_SPEED;
	if (!check_collision(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!check_collision(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/* Rotation vers la gauche */
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	// Rotation de la direction
	game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED)
		- game->player.dir_y * sin(-ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y
		* cos(-ROT_SPEED);
	// Rotation du plan caméra
	game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED)
		- game->player.plane_y * sin(-ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y
		* cos(-ROT_SPEED);
}

/* Rotation vers la droite */
void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	// Rotation de la direction
	game->player.dir_x = game->player.dir_x * cos(ROT_SPEED)
		- game->player.dir_y * sin(ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y
		* cos(ROT_SPEED);
	// Rotation du plan caméra
	game->player.plane_x = game->player.plane_x * cos(ROT_SPEED)
		- game->player.plane_y * sin(ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y
		* cos(ROT_SPEED);
}
