/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_normalize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:00:00 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 08:54:49 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	trim_trailing_spaces(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	while (len > 0 && line[len - 1] == ' ')
		len--;
	line[len] = '\0';
	return (len);
}

int	normalize_line(t_game *game, int i)
{
	size_t	current_len;
	char	*new_line;
	size_t	k;

	current_len = trim_trailing_spaces(game->map[i]);
	if (current_len < (size_t)game->map_width)
	{
		new_line = malloc(game->map_width + 1);
		if (!new_line)
			return (0);
		ft_memcpy(new_line, game->map[i], current_len);
		k = current_len;
		while (k < (size_t)game->map_width)
		{
			new_line[k] = '1';
			k++;
		}
		new_line[game->map_width] = '\0';
		free(game->map[i]);
		game->map[i] = new_line;
		ft_printf("Normalized line %d: '%s'\n", i, game->map[i]);
	}
	return (1);
}

int	normalize_map_lines(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if (!normalize_line(game, i))
			return (0);
		i++;
	}
	return (1);
}
