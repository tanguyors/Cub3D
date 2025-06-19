/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_spaces_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:40:00 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 09:19:15 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	alloc_visited(int ***visited, int width, int height)
{
	int	i;

	*visited = malloc(sizeof(int *) * height);
	if (!*visited)
		return (0);
	i = 0;
	while (i < height)
	{
		(*visited)[i] = calloc(width, sizeof(int));
		if (!(*visited)[i])
			return (0);
		i++;
	}
	return (1);
}

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	is_walkable(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	flood_fill(t_fillctx *ctx, int x, int y)
{
	if (x < 0 || y < 0 || x >= ctx->width || y >= ctx->height)
		return (0);
	if (ctx->visited[y][x])
		return (1);
	if (ctx->map[y][x] == '1')
		return (1);
	if (ctx->map[y][x] == ' ')
		return (0);
	ctx->visited[y][x] = 1;
	if (!flood_fill(ctx, x, y - 1))
		return (0);
	if (!flood_fill(ctx, x, y + 1))
		return (0);
	if (!flood_fill(ctx, x - 1, y))
		return (0);
	if (!flood_fill(ctx, x + 1, y))
		return (0);
	return (1);
}
