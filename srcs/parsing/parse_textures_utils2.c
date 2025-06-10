#include "cub3d.h"

int	parse_texture_if_valid(t_game *game, char *trimmed, int *texture_count)
{
	if (is_texture_identifier(trimmed))
	{
		if (!parse_texture(game, trimmed))
			return (0);
		(*texture_count)++;
	}
	return (1);
}

int	process_texture_line(t_game *game, char *line, int *texture_count)
{
	char	*trimmed;

	if (!line)
		return (1);
	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
	{
		free(line);
		return (0);
	}
	if (ft_strlen(trimmed) > 0)
	{
		if (!check_floor_ceiling_texture(trimmed)
			|| !parse_texture_if_valid(game, trimmed, texture_count))
		{
			free(trimmed);
			free(line);
			return (0);
		}
	}
	free(trimmed);
	return (1);
}

int	parse_textures(t_game *game, int fd)
{
	char	*line;
	int		texture_count;

	texture_count = 0;
	while ((line = get_next_line(fd)) != NULL && texture_count < 4)
	{
		if (!process_texture_line(game, line, &texture_count))
			return (0);
		free(line);
	}
	if (line)
		free(line);
	return (texture_count == 4);
}
