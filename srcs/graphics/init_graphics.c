/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:35:59 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 08:36:00 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_window(t_game *game)
{
	if (!game)
		return (0);
	if (!game->mlx)
	{
		game->mlx = mlx_init();
		if (!game->mlx)
			return (0);
	}
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!game->win)
		return (0);
	return (1);
}

static int	init_screen_image(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (0);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	return (1);
}

int	load_texture(t_game *game, int index)
{
	int	w;
	int	h;

	if (!game->textures[index].path)
		return (0);
	game->textures[index].img = mlx_xpm_file_to_image(game->mlx,
			game->textures[index].path, &w, &h);
	if (!game->textures[index].img)
	{
		ft_printf("Error loading texture %s\n", game->textures[index].path);
		return (0);
	}
	ft_printf("Loaded texture %d: %s (%dx%d)\n", index,
		game->textures[index].path, w, h);
	game->textures[index].width = w;
	game->textures[index].height = h;
	return (1);
}

int	init_graphics(t_game *game)
{
	int	i;

	if (!init_window(game))
	{
		ft_putstr_fd("Error\nFailed to initialize window\n", 2);
		return (0);
	}
	if (!init_screen_image(game))
	{
		ft_putstr_fd("Error\nFailed to create screen image\n", 2);
		mlx_destroy_window(game->mlx, game->win);
		return (0);
	}
	i = 0;
	while (i < 4)
	{
		if (!load_texture(game, i))
			return (0);
		i++;
	}
	return (1);
}
