/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:35:53 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 08:35:54 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_minimap(t_game *g)
{
	draw_map(g);
	draw_player(g);
}

int	game_loop(t_game *game)
{
	update_movements(game);
	fill_image_rect(game, game->ceiling_color, (t_rect){0, 0, WINDOW_WIDTH,
		WINDOW_HEIGHT / 2});
	fill_image_rect(game, game->floor_color, (t_rect){0, WINDOW_HEIGHT / 2,
		WINDOW_WIDTH, WINDOW_HEIGHT / 2});
	render_3d(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
