/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:39:02 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 08:39:06 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	close_window(t_game *param)
{
	if (param)
		free_game(param);
	exit(0);
	return (0);
}

void	free_map_grid(t_game *g)
{
	int	y;

	y = -1;
	if (g->map)
	{
		while (++y < g->map_height)
			free(g->map[y]);
		free(g->map);
	}
}

void	exit_with_error(t_game *g, const char *msg)
{
	if (g)
	{
		if (g->mlx)
		{
			if (g->win)
				mlx_destroy_window(g->mlx, g->win);
			mlx_destroy_display(g->mlx);
			free(g->mlx);
		}
		if (g->map)
			free_map(g->map, g->map_height);
		free_textures(g);
	}
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
