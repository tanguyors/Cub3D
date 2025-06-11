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

int	finalize_map(t_game *game, char *map_buffer)
{
	game->map = ft_split(map_buffer, '\n');
	free(map_buffer);
	if (!game->map)
		return (0);
	game->map_height = 0;
	while (game->map[game->map_height])
		game->map_height++;
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

int	process_pre_map_line(t_game *game, char *line, int *map_started,
		char **map_buffer, size_t *max_width)
{
	if (is_texture_identifier(line) || is_color_identifier(line))
	{
		if (!parse_textures_and_colors(game, line))
			return (0);
	}
	else if (is_map_line(line))
	{
		*map_started = 1;
		if (!handle_map_line(line, map_buffer, max_width))
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
