#include "cub3d.h"
#include <fcntl.h>

int	read_and_process_lines(t_game *game, int fd, char **map_buffer,
		size_t *max_width)
{
	char	*line;
	int		map_started;
	int		result;

	map_started = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!map_started)
			result = process_pre_map_line(game, line, &map_started, map_buffer,
					max_width);
		else
			result = process_map_line(line, map_buffer, max_width);
		free(line);
		if (result == 0)
			return (0);
		if (result == 2)
			break ;
	}
	return (1);
}

int	parse_file_single_pass(t_game *game, const char *filename)
{
	int		fd;
	char	*map_buffer;
	size_t	max_width;
	int		result;

	map_buffer = NULL;
	max_width = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	if (read_and_process_lines(game, fd, &map_buffer, &max_width))
	{
		game->map.width = (int)max_width;
		result = finalize_map(game, map_buffer);
	}
	close(fd);
	return (result);
}

int	parse_game_data(t_game *game, int argc, char **argv)
{
	(void)argc;
	if (!parse_file_single_pass(game, argv[1]))
		return (0);
	return (1);
}