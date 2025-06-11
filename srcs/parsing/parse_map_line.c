#include "cub3d.h"

int	normalize_line(t_game *game, int i)
{
	size_t	current_len;
	char	*new_line;
	size_t	k;

	current_len = ft_strlen(game->map[i]);
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
	char *temp_map;
	size_t max_width;

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