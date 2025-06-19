/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:35:06 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 11:10:10 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_wall(t_game *g, t_map_vars *vars, int x, int y)
{
	t_point	rotated;
	t_point	wall_center;
	t_rect	wall_rect;

	rotated.x = (x - g->player.pos_x) * vars->tile_size;
	rotated.y = (y - g->player.pos_y) * vars->tile_size;
	rotated.x = vars->center.x + rotated.x * vars->scale;
	rotated.y = vars->center.y + rotated.y * vars->scale;
	wall_rect.x = rotated.x - (vars->tile_size * vars->scale) / 2;
	wall_rect.y = rotated.y - (vars->tile_size * vars->scale) / 2;
	wall_rect.width = vars->tile_size * vars->scale;
	wall_rect.height = vars->tile_size * vars->scale;
	wall_center.x = wall_rect.x + wall_rect.width / 2;
	wall_center.y = wall_rect.y + wall_rect.height / 2;
	if (is_in_circle(wall_center, vars->center, vars->radius))
	{
		fill_image_rect(g, 0x505050, wall_rect);
	}
}

static void	draw_map_walls(t_game *g, t_map_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			if (g->map[y][x] == '1')
				draw_wall(g, vars, x, y);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_background(t_game *g, t_point center, int radius)
{
	int		x;
	int		y;
	t_point	point;

	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			point.x = x;
			point.y = y;
			if (is_in_circle(point, center, radius))
				fill_image_rect(g, 0x202020, (t_rect){x, y, 1, 1});
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *g)
{
	t_map_vars	vars;

	vars.tile_size = fmin(MINIMAP_WIDTH / g->map_width, MINIMAP_HEIGHT
			/ g->map_height);
	vars.center.x = MINIMAP_WIDTH / 2;
	vars.center.y = MINIMAP_HEIGHT / 2;
	vars.radius = MINIMAP_WIDTH / 2 - 2;
	vars.scale = 0.8;
	draw_minimap_background(g, vars.center, vars.radius);
	draw_map_walls(g, &vars);
}
