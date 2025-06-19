/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validation_borders.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:37:56 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 08:57:40 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_top_row(t_game *game)
{
	int	j;

	j = 0;
	while (j < game->map_width)
	{
		if (game->map[0][j] != '1')
		{
			ft_printf("Error: Invalid top border at (0, %d): %c\n", j,
				game->map[0][j]);
			return (0);
		}
		j++;
	}
	return (1);
}

static int	check_bottom_row(t_game *game)
{
	int	j;

	j = 0;
	while (j < game->map_width)
	{
		if (game->map[game->map_height - 1][j] != '1')
		{
			ft_printf("Error: Invalid bottom border at (%d, %d): %c\n",
				game->map_height - 1, j, game->map[game->map_height - 1][j]);
			return (0);
		}
		j++;
	}
	return (1);
}

static int	check_left_col(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] != '1')
		{
			ft_printf("Error: Invalid left border at (%d, 0): %c\n", i,
				game->map[i][0]);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_right_col(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][game->map_width - 1] != '1')
		{
			ft_printf("Error: Invalid right border at (%d, %d): %c\n", i,
				game->map_width - 1, game->map[i][game->map_width - 1]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_map_borders(t_game *game)
{
	if (!check_top_row(game))
		return (0);
	if (!check_bottom_row(game))
		return (0);
	if (!check_left_col(game))
		return (0);
	if (!check_right_col(game))
		return (0);
	return (1);
}
