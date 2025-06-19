/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:20:00 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 11:09:57 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			flood_fill(t_fillctx *ctx, int x, int y);

static int	validate_map_spaces_loop(t_game *game, t_fillctx *ctx,
		int **visited)
{
	int	i;
	int	j;
	int	valid;

	valid = 1;
	i = 0;
	while (i < game->map_height && valid)
	{
		j = 0;
		while (j < game->map_width && valid)
		{
			if (is_walkable(game->map[i][j]) && !visited[i][j])
			{
				if (!flood_fill(ctx, j, i))
				{
					ft_putstr_fd("Error\nMap is not closed (hole detected)\n",
						2);
					valid = 0;
				}
			}
			j++;
		}
		i++;
	}
	return (valid);
}

int	validate_map_spaces(t_game *game)
{
	int			**visited;
	int			valid;
	t_fillctx	ctx;

	if (!alloc_visited(&visited, game->map_width, game->map_height))
		return (0);
	ctx.map = game->map;
	ctx.visited = visited;
	ctx.width = game->map_width;
	ctx.height = game->map_height;
	valid = validate_map_spaces_loop(game, &ctx, visited);
	free_visited(visited, game->map_height);
	return (valid);
}
