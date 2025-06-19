/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:37:45 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 11:10:02 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_player_found_ctx(t_playerctx *ctx)
{
	if (*(ctx->player_count) > 0)
	{
		ft_putstr_fd("Error\nMultiple player start positions\n", 2);
		return (0);
	}
	ctx->game->player_pos_x = ctx->x + 0.5;
	ctx->game->player_pos_y = ctx->y + 0.5;
	ctx->game->player_dir = ctx->c;
	(*(ctx->player_count))++;
	return (1);
}

static int	check_player_count(int player_count)
{
	if (player_count == 0)
	{
		ft_putstr_fd("Error\nNo player start position found\n", 2);
		return (0);
	}
	return (1);
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	find_player_in_row(t_game *game, int y, int *player_count)
{
	int			x;
	t_playerctx	ctx;

	x = 0;
	while (x < game->map_width)
	{
		if (is_player_char(game->map[y][x]))
		{
			ctx.game = game;
			ctx.x = x;
			ctx.y = y;
			ctx.c = game->map[y][x];
			ctx.player_count = player_count;
			if (!handle_player_found_ctx(&ctx))
				return (0);
		}
		x++;
	}
	return (1);
}

int	parse_player_position(t_game *game)
{
	int	player_count;
	int	y;

	player_count = 0;
	y = 0;
	while (y < game->map_height)
	{
		if (!find_player_in_row(game, y, &player_count))
			return (0);
		y++;
	}
	return (check_player_count(player_count));
}
