/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils_fixed.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:00:00 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 11:10:44 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_rotation_angle(t_game *g)
{
	double	angle;

	angle = atan2(g->player.dir_y, g->player.dir_x);
	if (angle > 3.14159265358979323846)
		angle -= 2 * 3.14159265358979323846;
	else if (angle < -3.14159265358979323846)
		angle += 2 * 3.14159265358979323846;
	return (angle);
}

void	init_map_vars(t_game *g, t_map_vars *vars)
{
	vars->tile_size = fmin(MINIMAP_WIDTH / g->map_width, MINIMAP_HEIGHT
			/ g->map_height);
	vars->center.x = MINIMAP_WIDTH / 2;
	vars->center.y = MINIMAP_HEIGHT / 2;
	vars->radius = MINIMAP_WIDTH / 2 - 2;
	vars->scale = 0.8;
}

void	calculate_wall_coords(t_game *g, t_map_vars *vars, t_point *rotated,
		t_point pos)
{
	t_wall_calc	calc;

	calc.rel_x = (pos.x - g->player.pos_x) * vars->tile_size;
	calc.rel_y = (pos.y - g->player.pos_y) * vars->tile_size;
	calc.angle = get_rotation_angle(g);
	rotated->x = calc.rel_x * cos(calc.angle) - calc.rel_y * sin(calc.angle);
	rotated->y = calc.rel_x * sin(calc.angle) + calc.rel_y * cos(calc.angle);
	rotated->x = vars->center.x + rotated->x * vars->scale;
	rotated->y = vars->center.y + rotated->y * vars->scale;
}
