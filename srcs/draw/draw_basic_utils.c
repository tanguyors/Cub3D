/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basic_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:10:00 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 10:51:50 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_rectangle(t_game *game, t_point pos, t_point size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			draw_pixel(game, pos.x + j, pos.y + i, color);
			j++;
		}
		i++;
	}
}

void	fill_image_circle(t_game *g, int color, t_point center, int radius)
{
	int	px;
	int	py;
	int	y;
	int	x;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				px = center.x + x;
				py = center.y + y;
				draw_pixel(g, px, py, color);
			}
			x++;
		}
		y++;
	}
}

void	fill_image_rect(t_game *g, int color, t_rect rect)
{
	int	pixel;
	int	y;
	int	x;

	y = rect.y;
	while (y < rect.y + rect.height)
	{
		x = rect.x;
		while (x < rect.x + rect.width)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
			{
				pixel = y * g->line_length + x * (g->bits_per_pixel / 8);
				*(int *)(g->addr + pixel) = color;
			}
			x++;
		}
		y++;
	}
}
