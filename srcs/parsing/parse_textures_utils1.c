/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:38:23 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 08:52:03 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_index(char *identifier)
{
	if (ft_strncmp(identifier, "NO", 2) == 0)
		return (0);
	if (ft_strncmp(identifier, "SO", 2) == 0)
		return (1);
	if (ft_strncmp(identifier, "WE", 2) == 0)
		return (2);
	if (ft_strncmp(identifier, "EA", 2) == 0)
		return (3);
	return (-1);
}

int	validate_texture_parts(char **parts)
{
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		ft_printf("Error: Invalid texture line format\n");
		if (parts)
			free_tab(parts);
		return (0);
	}
	return (1);
}

int	handle_texture_path(t_game *game, char **parts, int index)
{
	char	*trimmed;
	char	*path;

	trimmed = ft_strtrim(parts[1], " \t\n\r");
	if (!trimmed)
	{
		free_tab(parts);
		return (0);
	}
	path = ft_strdup(trimmed);
	free(trimmed);
	if (!path)
	{
		free_tab(parts);
		return (0);
	}
	if (game->textures[index].path)
		free(game->textures[index].path);
	game->textures[index].path = path;
	return (1);
}

int	parse_texture(t_game *game, char *line)
{
	char	**parts;
	int		index;

	parts = ft_split(line, ' ');
	if (!validate_texture_parts(parts))
		return (0);
	index = get_texture_index(parts[0]);
	if (index == -1)
	{
		ft_printf("Error: Invalid texture identifier\n");
		free_tab(parts);
		return (0);
	}
	if (!handle_texture_path(game, parts, index))
		return (0);
	free_tab(parts);
	return (1);
}

int	check_floor_ceiling_texture(char *trimmed)
{
	if (ft_strncmp(trimmed, "FT ", 3) == 0 || ft_strncmp(trimmed, "CT ",
			3) == 0)
	{
		ft_printf("Error: Floor/ceiling textures not supported.\n");
		return (0);
	}
	return (1);
}
