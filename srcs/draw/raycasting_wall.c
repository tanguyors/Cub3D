#include "../includes/cub3d.h"

void	calculate_wall_height(t_game *g, t_ray_vars *vars)
{
	(void)g;
	if (vars->side == 0)
		vars->perp_wall_dist = (vars->side_dist_x - vars->delta_dist_x);
	else
		vars->perp_wall_dist = (vars->side_dist_y - vars->delta_dist_y);
	vars->line_height = (int)(WINDOW_HEIGHT / vars->perp_wall_dist);
	vars->draw_start = -vars->line_height / 2 + WINDOW_HEIGHT / 2;
	if (vars->draw_start < 0)
		vars->draw_start = 0;
	vars->draw_end = vars->line_height / 2 + WINDOW_HEIGHT / 2;
	if (vars->draw_end >= WINDOW_HEIGHT)
		vars->draw_end = WINDOW_HEIGHT - 1;
}

void	calculate_texture_coords(t_game *g, t_ray_vars *vars)
{
	if (vars->side == 0)
		vars->tex_num = vars->ray_dir_x > 0 ? 3 : 2;
	else
		vars->tex_num = vars->ray_dir_y > 0 ? 1 : 0;
	if (vars->side == 0)
		vars->wall_x = g->player.pos_y + vars->perp_wall_dist * vars->ray_dir_y;
	else
		vars->wall_x = g->player.pos_x + vars->perp_wall_dist * vars->ray_dir_x;
	vars->wall_x -= floor(vars->wall_x);
	vars->tex_x = (int)(vars->wall_x * g->textures[vars->tex_num].width);
	if (vars->side == 0 && vars->ray_dir_x > 0)
		vars->tex_x = g->textures[vars->tex_num].width - vars->tex_x - 1;
	if (vars->side == 1 && vars->ray_dir_y < 0)
		vars->tex_x = g->textures[vars->tex_num].width - vars->tex_x - 1;
	vars->step = 1.0 * g->textures[vars->tex_num].height / vars->line_height;
	vars->tex_pos = (vars->draw_start - WINDOW_HEIGHT / 2 + vars->line_height
			/ 2) * vars->step;
}

void	draw_wall_stripe(t_game *g, t_ray_vars *vars, int x)
{
	t_rect	wall_stripe;
	int		color;
	int		y;

	wall_stripe.x = x;
	wall_stripe.width = 1;
	y = vars->draw_start;
	while (y < vars->draw_end)
	{
		vars->tex_y = (int)vars->tex_pos & (g->textures[vars->tex_num].height
				- 1);
		vars->tex_pos += vars->step;
		color = *(int *)(g->textures[vars->tex_num].addr + (vars->tex_y
					* g->textures[vars->tex_num].line_length + vars->tex_x
					* (g->textures[vars->tex_num].bits_per_pixel / 8)));
		if (vars->side == 1)
			color = (color >> 1) & 8355711;
		wall_stripe.y = y;
		wall_stripe.height = 1;
		fill_image_rect(g, color, wall_stripe);
		y++;
	}
}
