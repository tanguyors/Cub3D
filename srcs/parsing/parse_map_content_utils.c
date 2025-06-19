/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_content_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:30:00 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 09:50:14 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	finalize_map_borders(t_game *game)
{
	if (!check_raw_map_borders(game->map, game->map_height))
	{
		ft_putstr_fd("Error\nInvalid map border (raw)\n", 2);
		return (0);
	}
	if (!normalize_map_lines(game))
		return (0);
	if (!validate_map_borders(game))
	{
		ft_putstr_fd("Error\nInvalid map border\n", 2);
		return (0);
	}
	return (1);
}

int	finalize_map_validation(t_game *game)
{
	if (!validate_map_spaces(game))
	{
		ft_putstr_fd("Error\nMap is not closed (hole detected)\n", 2);
		return (0);
	}
	if (!parse_player_position(game))
		return (0);
	if (!validate_map_chars(game))
	{
		ft_putstr_fd("Error\nInvalid character in map\n", 2);
		return (0);
	}
	return (1);
}
