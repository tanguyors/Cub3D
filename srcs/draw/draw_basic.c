/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:35:00 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 11:08:00 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	set_line_direction(t_line_dir dir, int *sx, int *sy)
{
	if (dir.start_x < dir.end_x)
		*sx = 1;
	else
		*sx = -1;
	if (dir.start_y < dir.end_y)
		*sy = 1;
	else
		*sy = -1;
}

static void	update_line_error(t_line_vars *vars, t_point *pos)
{
	int	e2;

	e2 = 2 * vars->err;
	if (e2 > -vars->dy)
	{
		vars->err -= vars->dy;
		pos->x += vars->sx;
	}
	if (e2 < vars->dx)
	{
		vars->err += vars->dx;
		pos->y += vars->sy;
	}
}

static void	init_line_vars(t_line_dir dir, t_line_vars *vars)
{
	vars->dx = abs(dir.end_x - dir.start_x);
	vars->dy = abs(dir.end_y - dir.start_y);
	set_line_direction(dir, &vars->sx, &vars->sy);
	vars->err = vars->dx - vars->dy;
}

void	draw_line(t_game *game, t_point start, t_point end, int color)
{
	t_line_vars	vars;
	t_line_dir	dir;
	t_point		pos;

	dir.start_x = start.x;
	dir.end_x = end.x;
	dir.start_y = start.y;
	dir.end_y = end.y;
	init_line_vars(dir, &vars);
	pos = start;
	while (1)
	{
		draw_pixel(game, pos.x, pos.y, color);
		if (pos.x == end.x && pos.y == end.y)
			break ;
		update_line_error(&vars, &pos);
	}
}
