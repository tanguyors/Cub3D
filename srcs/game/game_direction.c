#include "cub3d.h"

static void	set_north_direction(t_game *g)
{
	g->player.dir_x = 0;
	g->player.dir_y = -1;
	g->player.plane_x = 0.66;
	g->player.plane_y = 0;
}

static void	set_south_direction(t_game *g)
{
	g->player.dir_x = 0;
	g->player.dir_y = 1;
	g->player.plane_x = -0.66;
	g->player.plane_y = 0;
}

static void	set_east_direction(t_game *g)
{
	g->player.dir_x = 1;
	g->player.dir_y = 0;
	g->player.plane_x = 0;
	g->player.plane_y = 0.66;
}

static void	set_west_direction(t_game *g)
{
	g->player.dir_x = -1;
	g->player.dir_y = 0;
	g->player.plane_x = 0;
	g->player.plane_y = -0.66;
}

void	set_initial_direction(t_game *g)
{
	g->player.dir_x = 0;
	g->player.dir_y = 0;
	g->player.plane_x = 0;
	g->player.plane_y = 0;
	if (g->player_dir == 'N')
		set_north_direction(g);
	else if (g->player_dir == 'S')
		set_south_direction(g);
	else if (g->player_dir == 'E')
		set_east_direction(g);
	else if (g->player_dir == 'W')
		set_west_direction(g);
}
