/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:35:23 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 08:35:24 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_floor_ceiling(t_game *g)
{
	t_rect	floor;
	t_rect	ceiling;

	floor.x = 0;
	floor.y = WINDOW_HEIGHT / 2;
	floor.width = WINDOW_WIDTH;
	floor.height = WINDOW_HEIGHT / 2;
	fill_image_rect(g, g->floor_color, floor);
	ceiling.x = 0;
	ceiling.y = 0;
	ceiling.width = WINDOW_WIDTH;
	ceiling.height = WINDOW_HEIGHT / 2;
	fill_image_rect(g, g->ceiling_color, ceiling);
}

void	render_3d(t_game *g)
{
	int	x;

	draw_floor_ceiling(g);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cast_ray(g, x);
		x++;
	}
}
