#include "cub3d.h"
#include <fcntl.h>

int			parse_color_line(t_game *game, char *line);
int			normalize_map_lines(t_game *game);
int			parse_player_position(t_game *game);

static int	parse_file_single_pass(t_game *game, const char *filename)
{
	int		fd;
	char	*line;
	char	*map_buffer;
	size_t	max_width;
	int		map_started;
	char	*tmp;

	map_buffer = NULL;
	max_width = 0;
	map_started = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_texture_identifier(line))
		{
			if (!parse_texture(game, line))
			{
				free(line);
				close(fd);
				return (0);
			}
		}
		else if (is_color_identifier(line))
		{
			if (!parse_color_line(game, line))
			{
				free(line);
				close(fd);
				return (0);
			}
		}
		else if (is_map_line(line))
		{
			map_started = 1;
			if (map_buffer)
			{
				tmp = map_buffer;
				map_buffer = ft_strjoin(map_buffer, "\n");
				free(tmp);
				tmp = map_buffer;
				map_buffer = ft_strjoin(map_buffer, line);
				free(tmp);
			}
			else
				map_buffer = ft_strdup(line);
			if (ft_strlen(line) > max_width)
				max_width = ft_strlen(line);
		}
		else if (map_started && ft_strlen(line) > 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
	close(fd);
	if (!map_buffer)
		return (0);
	game->map.width = (int)max_width;
	game->map.grid = ft_split(map_buffer, '\n');
	free(map_buffer);
	if (!game->map.grid)
		return (0);
	game->map.height = 0;
	while (game->map.grid[game->map.height])
		game->map.height++;
	if (!normalize_map_lines(game))
		return (0);
	if (!parse_player_position(game))
		return (0);
	if (!check_map_chars(game))
	{
		ft_putstr_fd("Error\nInvalid character in map\n", 2);
		return (0);
	}
	return (1);
}

int	parse_game_data(t_game *game, int argc, char **argv)
{
	(void)argc;
	if (!parse_file_single_pass(game, argv[1]))
		return (0);
	return (1);
}
