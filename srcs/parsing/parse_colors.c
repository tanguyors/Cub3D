#include "cub3d.h"

// int	is_color_identifier(char *line)
// {
// 	if (!line || ft_strlen(line) < 2)
// 		return (0);
// 	return ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ');
// }

int	parse_and_validate_color_values(char **split, int *r, int *g, int *b)
{
	char	**rgb;

	rgb = ft_split(split[1], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_tab(split);
		if (rgb)
			free_tab(rgb);
		return (0);
	}
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	free_tab(rgb);
	return (*r >= 0 && *r <= 255 && *g >= 0 && *g <= 255 && *b >= 0
		&& *b <= 255);
}

int	parse_color_line(t_game *game, char *line)
{
	char	**split;
	int		*target_color;
	int		r;
	int		g;
	int		b;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
	{
		if (split)
			free_tab(split);
		return (0);
	}
	target_color = NULL;
	if (ft_strncmp(split[0], "F", 2) == 0)
		target_color = &game->map.floor_color;
	else if (ft_strncmp(split[0], "C", 2) == 0)
		target_color = &game->map.ceiling_color;
	if (!target_color || !parse_and_validate_color_values(split, &r, &g, &b))
	{
		free_tab(split);
		return (0);
	}
	*target_color = r * 65536 + g * 256 + b;
	return (free_tab(split), 1);
}

int	parse_colors(t_game *game, int fd)
{
	char	*line;
	int		colors_found;

	colors_found = 0;
	while ((line = get_next_line(fd)) != NULL && colors_found < 2)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strlen(line) > 0 && is_color_identifier(line))
		{
			if (!parse_color_line(game, line))
			{
				free(line);
				return (0);
			}
			colors_found++;
		}
		free(line);
	}
	if (line)
		free(line);
	return (colors_found == 2);
}
