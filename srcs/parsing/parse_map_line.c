/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:37:25 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 11:09:55 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

static int	validate_map_line_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!validate_map_char(line[i]))
		{
			ft_printf("Error: Invalid character in map: %c\n", line[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	validate_map_line_length(char *line, int width)
{
	int	len;

	len = 0;
	while (line[len])
		len++;
	if (len > width)
	{
		ft_printf("Error: Map line too long\n");
		return (0);
	}
	return (1);
}

int	parse_map_line(t_game *game, char *line)
{
	if (!line)
		return (0);
	if (!validate_map_line_chars(line))
		return (0);
	if (!validate_map_line_length(line, game->map_width))
		return (0);
	return (1);
}

int	parse_map(t_game *game, int fd)
{
	char	*temp_map;
	size_t	max_width;

	if (!init_map_reading(game, fd))
		return (0);
	temp_map = read_map_lines(game, fd, &max_width);
	if (!temp_map)
		return (0);
	game->map_width = (int)max_width;
	game->map = ft_split(temp_map, '\n');
	free(temp_map);
	if (!game->map)
		return (0);
	if (!normalize_map_lines(game))
		return (0);
	if (!parse_player_position(game))
		return (0);
	if (!validate_map_chars(game))
	{
		ft_putstr_fd("Error\nInvalid character in map\n", 2);
		return (0);
	}
	return (1);
}
