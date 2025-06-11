#include "../includes/cub3d.h"

static void	init_ray_vars(t_game *g, int x, t_ray_vars *vars)
{
	vars->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	vars->ray_dir_x = g->player.dir_x + g->player.plane_x * vars->camera_x;
	vars->ray_dir_y = g->player.dir_y + g->player.plane_y * vars->camera_x;
	vars->map_x = (int)g->player.pos_x;
	vars->map_y = (int)g->player.pos_y;
	vars->delta_dist_x = fabs(1 / vars->ray_dir_x);
	vars->delta_dist_y = fabs(1 / vars->ray_dir_y);
	vars->hit = 0;
}

static void	calculate_step_and_side_dist(t_game *g, t_ray_vars *vars)
{
	if (vars->ray_dir_x < 0)
	{
		vars->step_x = -1;
		vars->side_dist_x = (g->player.pos_x - vars->map_x)
			* vars->delta_dist_x;
	}
	else
	{
		vars->step_x = 1;
		vars->side_dist_x = (vars->map_x + 1.0 - g->player.pos_x)
			* vars->delta_dist_x;
	}
	if (vars->ray_dir_y < 0)
	{
		vars->step_y = -1;
		vars->side_dist_y = (g->player.pos_y - vars->map_y)
			* vars->delta_dist_y;
	}
	else
	{
		vars->step_y = 1;
		vars->side_dist_y = (vars->map_y + 1.0 - g->player.pos_y)
			* vars->delta_dist_y;
	}
}

static void	perform_dda(t_game *g, t_ray_vars *vars)
{
	while (vars->hit == 0)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += vars->step_x;
			vars->side = 0;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += vars->step_y;
			vars->side = 1;
		}
		if (vars->map_y >= 0 && vars->map_y < g->map_height && vars->map_x >= 0
			&& vars->map_x < g->map_width)
		{
			if (g->map[vars->map_y][vars->map_x] == '1')
				vars->hit = 1;
		}
	}
}

void	cast_ray(t_game *g, int x)
{
	t_ray_vars	vars;

	init_ray_vars(g, x, &vars);
	calculate_step_and_side_dist(g, &vars);
	perform_dda(g, &vars);
	calculate_wall_height(g, &vars);
	calculate_texture_coords(g, &vars);
	draw_wall_stripe(g, &vars, x);
}
