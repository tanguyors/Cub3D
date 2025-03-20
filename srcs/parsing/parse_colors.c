#include "cub3d.h"

int	is_color_identifier(char *line)
{
	if (!line || ft_strlen(line) < 2)
		return (0);
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (1);
	return (0);
}

static int	ft_is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid_rgb(char **rgb)
{
	int	i;
	int	value;

	i = 0;
	while (rgb[i])
	{
		if (!ft_is_str_digit(rgb[i]))
			return (0);
		value = ft_atoi(rgb[i]);
		if (value < 0 || value > 255)
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

static int	convert_rgb_to_int(char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	return ((r << 16) | (g << 8) | b);
}

static int	parse_color_line(t_game *game, char *line)
{
	char	**split;
	char	**rgb_split;
	int		color;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
	{
		ft_printf("Erreur: Format de couleur invalide\n");
		if (split)
			free_tab(split);
		return (0);
	}
	rgb_split = ft_split(split[1], ',');
	if (!rgb_split || !is_valid_rgb(rgb_split))
	{
		ft_printf("Erreur: Format RGB invalide\n");
		if (split)
			free_tab(split);
		if (rgb_split)
			free_tab(rgb_split);
		return (0);
	}
	color = convert_rgb_to_int(rgb_split);
	if (!ft_strncmp(split[0], "F", 1))
		game->map.floor_color = color;
	else if (!ft_strncmp(split[0], "C", 1))
		game->map.ceiling_color = color;
	free_tab(split);
	free_tab(rgb_split);
	return (1);
}

int	parse_colors(t_game *game, int fd)
{
	char	*line;
	int		color_count;

	color_count = 0;
	while ((line = get_next_line(fd)) != NULL && color_count < 2)
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
			color_count++;
		}
		free(line);
	}
	if (color_count != 2)
	{
		ft_printf("Erreur: Il manque des définitions de couleurs\n");
		return (0);
	}
	return (1);
}

