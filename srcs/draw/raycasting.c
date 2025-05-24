#include <cub3d.h>

void	cast_ray(t_game *g, int x)
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;
	t_rect	wall_stripe;

	camera_x = 2 * x / (double)g->win_width - 1;
	ray_dir_x = g->player.dir_x + g->player.plane_x * camera_x;
	ray_dir_y = g->player.dir_y + g->player.plane_y * camera_x;
	map_x = (int)g->player.pos_x;
	map_y = (int)g->player.pos_y;
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	hit = 0;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (g->player.pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - g->player.pos_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (g->player.pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - g->player.pos_y) * delta_dist_y;
	}
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (map_y >= 0 && map_y < g->map.height && map_x >= 0
			&& map_x < g->map.width)
		{
			if (g->map.grid[map_y][map_x] == '1')
				hit = 1;
		}
	}
	if (side == 0)
		perp_wall_dist = (side_dist_x - delta_dist_x);
	else
		perp_wall_dist = (side_dist_y - delta_dist_y);
	line_height = (int)(g->win_height / perp_wall_dist);
	draw_start = -line_height / 2 + g->win_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + g->win_height / 2;
	if (draw_end >= g->win_height)
		draw_end = g->win_height - 1;
	if (side == 0)
		tex_num = ray_dir_x > 0 ? 3 : 2; // EA or WE
	else
		tex_num = ray_dir_y > 0 ? 1 : 0; // SO or NO
	if (side == 0)
		wall_x = g->player.pos_y + perp_wall_dist * ray_dir_y;
	else
		wall_x = g->player.pos_x + perp_wall_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * g->textures[tex_num].width);
	if (side == 0 && ray_dir_x > 0)
		tex_x = g->textures[tex_num].width - tex_x - 1;
	if (side == 1 && ray_dir_y < 0)
		tex_x = g->textures[tex_num].width - tex_x - 1;
	step = 1.0 * g->textures[tex_num].height / line_height;
	tex_pos = (draw_start - g->win_height / 2 + line_height / 2) * step;
	wall_stripe.x = x;
	wall_stripe.width = 1;
	for (int y = draw_start; y < draw_end; y++)
	{
		tex_y = (int)tex_pos & (g->textures[tex_num].height - 1);
		tex_pos += step;
		color = *(int *)(g->textures[tex_num].img_data + (tex_y
					* g->textures[tex_num].line_length + tex_x
					* (g->textures[tex_num].bits_per_pixel / 8)));
		if (side == 1)
			color = (color >> 1) & 8355711;
		wall_stripe.y = y;
		wall_stripe.height = 1;
		fill_image_rect(g, color, wall_stripe);
	}
}

void	draw_floor_ceiling(t_game *g)
{
	float	ray_dir_x0;
	float	ray_dir_y0;
	float	ray_dir_x1;
	float	ray_dir_y1;
	int		p;
	float	pos_z;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		color;
	t_rect	pixel;

	for (int y = g->win_height / 2; y < g->win_height; y++)
	{
		ray_dir_x0 = g->player.dir_x - g->player.plane_x;
		ray_dir_y0 = g->player.dir_y - g->player.plane_y;
		ray_dir_x1 = g->player.dir_x + g->player.plane_x;
		ray_dir_y1 = g->player.dir_y + g->player.plane_y;
		p = y - g->win_height / 2;
		pos_z = 0.5 * g->win_height;
		row_distance = pos_z / p;
		floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / g->win_width;
		floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / g->win_width;
		floor_x = g->player.pos_x + row_distance * ray_dir_x0;
		floor_y = g->player.pos_y + row_distance * ray_dir_y0;
		pixel.height = 1;
		pixel.width = 1;
		pixel.y = y;
		for (int x = 0; x < g->win_width; x++)
		{
			cell_x = (int)floor_x;
			cell_y = (int)floor_y;
			tx = (int)(g->textures[4].width * (floor_x
						- cell_x)) & (g->textures[4].width - 1);
			ty = (int)(g->textures[4].height * (floor_y
						- cell_y)) & (g->textures[4].height - 1);
			floor_x += floor_step_x;
			floor_y += floor_step_y;
			pixel.x = x;
			color = *(int *)(g->textures[4].img_data + (ty
						* g->textures[4].line_length + tx
						* (g->textures[4].bits_per_pixel / 8)));
			fill_image_rect(g, color, pixel);
			pixel.y = g->win_height - y - 1;
			color = *(int *)(g->textures[5].img_data + (ty
						* g->textures[5].line_length + tx
						* (g->textures[5].bits_per_pixel / 8)));
			fill_image_rect(g, color, pixel);
		}
	}
}

void	render_3d(t_game *g)
{
	int x;

	if (g->textures[4].img && g->textures[5].img)
		draw_floor_ceiling(g);
	else
	{
		fill_image_rect(g, g->map.ceiling_color, (t_rect){0, 0, g->win_width,
			g->win_height / 2});
		fill_image_rect(g, g->map.floor_color, (t_rect){0, g->win_height / 2,
			g->win_width, g->win_height / 2});
	}
	x = 0;
	while (x < g->win_width)
	{
		cast_ray(g, x);
		x++;
	}
}