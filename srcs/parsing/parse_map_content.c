/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:37:07 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 11:10:05 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_textures_and_colors(t_game *game, char *line)
{
	if (is_texture_identifier(line))
	{
		if (!parse_texture(game, line))
			return (0);
	}
	else if (is_color_identifier(line))
	{
		if (!parse_color_line(game, line))
			return (0);
	}
	return (1);
}

int	handle_map_line(char *line, char **map_buffer, size_t *max_width)
{
	char	*tmp;

	if (map_buffer[0])
	{
		tmp = map_buffer[0];
		map_buffer[0] = ft_strjoin(map_buffer[0], "\n");
		free(tmp);
		tmp = map_buffer[0];
		map_buffer[0] = ft_strjoin(map_buffer[0], line);
		free(tmp);
	}
	else
		map_buffer[0] = ft_strdup(line);
	if (ft_strlen(line) > *max_width)
		*max_width = ft_strlen(line);
	return (1);
}

static int	finalize_map_split_and_count(t_game *game, char *map_buffer)
{
	game->map = ft_split(map_buffer, '\n');
	free(map_buffer);
	if (!game->map)
		return (0);
	game->map_height = 0;
	while (game->map[game->map_height])
		game->map_height++;
	return (1);
}

int	finalize_map(t_game *game, char *map_buffer)
{
	if (!finalize_map_split_and_count(game, map_buffer))
		return (0);
	if (!finalize_map_borders(game))
	{
		free_tab(game->map);
		game->map = NULL;
		return (0);
	}
	if (!finalize_map_validation(game))
	{
		free_tab(game->map);
		game->map = NULL;
		return (0);
	}
	return (1);
}

int	process_map_line(char *line, char **map_buffer, size_t *max_width)
{
	if (is_map_line(line))
	{
		if (!handle_map_line(line, map_buffer, max_width))
			return (0);
	}
	else if (ft_strlen(line) > 0)
		return (2);
	return (1);
}
