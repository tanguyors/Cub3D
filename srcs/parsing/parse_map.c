#include "cub3d.h"

static int	init_map_reading(t_game *game, int fd)
{
	if (fd < 0 || !game)
		return (0);
	game->map.height = 0;
	ft_printf("Starting to read map...\n");
	return (1);
}

static char	*handle_line(char *line, char *temp_map, size_t *max_width)
{
	char	*temp;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	ft_printf("Read line: %s\n", line);
	if (ft_strlen(line) > *max_width)
		*max_width = ft_strlen(line);
	if (!temp_map)
		return (ft_strdup(line));
	temp = temp_map;
	temp_map = ft_strjoin(temp_map, "\n");
	free(temp);
	temp = temp_map;
	temp_map = ft_strjoin(temp_map, line);
	free(temp);
	return (temp_map);
}

static int is_map_line(char *line)
{
	int i;
	
	if (!line || ft_strlen(line) == 0)
		return (0);
		
	if (is_texture_identifier(line) || is_color_identifier(line))
		return (0);
		
	i = 0;
	while (line[i])
	{
		if (line[i] == '1')
			return (1);
		i++;
	}
	
	return (0);
}

static char	*read_map_lines(t_game *game, int fd, size_t *max_width)
{
	char	*line;
	char	*temp_map;
	int		map_started = 0;

	temp_map = NULL;
	*max_width = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
			
		if (is_map_line(line))
		{
			if (map_started && ft_strlen(line) == 0)
			{
				free(line);
				break;
			}
			map_started = 1;
			temp_map = handle_line(line, temp_map, max_width);
			game->map.height++;
		}
		else if (map_started)
		{
			free(line);
			break;
		}
		free(line);
	}
	return (temp_map);
}

static int	normalize_line(t_game *game, int i)
{
	size_t	current_len;
	char	*new_line;
	size_t	k;

	current_len = ft_strlen(game->map.grid[i]);
	if (current_len < (size_t)game->map.width)
	{
		new_line = malloc(game->map.width + 1);
		if (!new_line)
			return (0);
		ft_memcpy(new_line, game->map.grid[i], current_len);
		k = current_len;
		while (k < (size_t)game->map.width)
		{
			new_line[k] = '1';
			k++;
		}
		new_line[game->map.width] = '\0';
		free(game->map.grid[i]);
		game->map.grid[i] = new_line;
		ft_printf("Normalized line %d: '%s'\n", i, game->map.grid[i]);
	}
	return (1);
}

static int	normalize_map_lines(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		if (!normalize_line(game, i))
			return (0);
		i++;
	}
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
	game->map.width = (int)max_width;
	game->map.grid = ft_split(temp_map, '\n');
	free(temp_map);
	if (!game->map.grid)
		return (0);
	if (!normalize_map_lines(game))
		return (0);
	if (!check_map_chars(game))
	{
		ft_putstr_fd("Error\nInvalid character in map\n", 2);
		return (0);
	}
	return (1);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || 
		c == 'E' || c == 'W' || c == ' ');
}

static int	validate_player_count(int player_count)
{
	if (player_count != 1)
	{
		ft_printf("Error: Map must contain exactly one player position");
		ft_printf(" (found %d)\n", player_count);
		return (0);
	}
	return (1);
}

int	check_map_chars(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (!is_valid_char(game->map.grid[i][j]))
			{
				ft_printf("Invalid char '%c' (ASCII: %d) at [%d][%d]\n", 
					game->map.grid[i][j], (int)game->map.grid[i][j], i, j);
				return (0);
			}
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S' ||
				game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	return (validate_player_count(player_count));
}

static int	is_space_or_player(char c)
{
	if (c == '0' || c == 'W' || c == 'N' || c == 'S' || c == 'E')
		return (1);
	return (0);
}

static int	check_horizontal_borders(t_map *map)
{
	int	j;

	j = 0;
	while (j < map->width)
	{
		if (is_space_or_player(map->grid[0][j]) || 
			is_space_or_player(map->grid[map->height - 1][j]))
			return (0);
		j++;
	}
	return (1);
}

static int	check_vertical_borders(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (is_space_or_player(map->grid[i][0]) || 
			is_space_or_player(map->grid[i][map->width - 1]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_spaces_around(t_map *map)
{
	int	i;
	int	j;

	i = 1;
	while (i < map->height - 1)
	{
		j = 1;
		while (j < map->width - 1)
		{
			if (is_space_or_player(map->grid[i][j]))
			{
				if (map->grid[i-1][j] == ' ' || map->grid[i+1][j] == ' ' ||
					map->grid[i][j-1] == ' ' || map->grid[i][j+1] == ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_borders(t_map *map)
{
	if (!check_horizontal_borders(map))
		return (0);
	if (!check_vertical_borders(map))
		return (0);
	if (!check_spaces_around(map))
		return (0);
	return (1);
}