#include "cub3d.h"

int	parse_texture_line(t_game *game, char *line)
{
	if (!is_texture_identifier(line))
		return (0);
	return (parse_texture(game, line));
}

int	is_texture_identifier(char *line)
{
	if (!line)
		return (0);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "FT ", 3) == 0 
			|| ft_strncmp(line, "CT ", 3) == 0);
}

static int	get_texture_index(char *identifier)
{
	if (ft_strncmp(identifier, "NO", 2) == 0)
		return (0);
	if (ft_strncmp(identifier, "SO", 2) == 0)
		return (1);
	if (ft_strncmp(identifier, "WE", 2) == 0)
		return (2);
	if (ft_strncmp(identifier, "EA", 2) == 0)
		return (3);
	if (ft_strncmp(identifier, "FT", 2) == 0)
		return (4);
	if (ft_strncmp(identifier, "CT", 2) == 0)
		return (5);
	return (-1);
}

int	parse_texture(t_game *game, char *line)
{
	char	**parts;
	int		index;
	char	*trimmed;
	char	*path;

	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		ft_printf("Error: Invalid texture line format\n");
		if (parts)
			free_tab(parts);
		return (0);
	}
	index = get_texture_index(parts[0]);
	if (index == -1)
	{
		ft_printf("Error: Invalid texture identifier\n");
		free_tab(parts);
		return (0);
	}
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
	free_tab(parts);
	return (1);
}

static int	process_texture_line(t_game *game, char *line, int *texture_count)
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
	if (ft_strlen(trimmed) > 0 && is_texture_identifier(trimmed))
	{
		if (!parse_texture(game, trimmed))
		{
			free(trimmed);
			free(line);
			return (0);
		}
		(*texture_count)++;
	}
	free(trimmed);
	return (1);
}

int	parse_textures(t_game *game, int fd)
{
	char	*line;
	int		texture_count;

	texture_count = 0;
	while ((line = get_next_line(fd)) != NULL && texture_count < 6)
	{
		if (!process_texture_line(game, line, &texture_count))
			return (0);
		free(line);
	}
	if (line)
		free(line);
	return (1);
}
