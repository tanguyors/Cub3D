#include "cub3d.h"

int	is_texture_identifier(char *line)
{
	if (!line || ft_strlen(line) < 3)
		return (0);
	
	// Vérifier le premier caractère et le second séparément
	if ((line[0] == 'N' && line[1] == 'O' && line[2] == ' ') ||
		(line[0] == 'S' && line[1] == 'O' && line[2] == ' ') ||
		(line[0] == 'W' && line[1] == 'E' && line[2] == ' ') ||
		(line[0] == 'E' && line[1] == 'A' && line[2] == ' '))
		return (1);
	return (0);
}

static int	get_texture_index(char *identifier)
{
	if (!ft_strncmp(identifier, "NO", 2))
		return (0);
	if (!ft_strncmp(identifier, "SO", 2))
		return (1);
	if (!ft_strncmp(identifier, "WE", 2))
		return (2);
	if (!ft_strncmp(identifier, "EA", 2))
		return (3);
	return (-1);
}

static int	parse_texture_line(t_game *game, char *line)
{
	char	**split;
	int		index;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
	{
		ft_printf("Erreur: Format de texture invalide\n");
		if (split)
			free_tab(split);
		return (0);
	}
	index = get_texture_index(split[0]);
	if (index == -1 || game->textures[index].path)
	{
		ft_printf("Erreur: Identifiant invalide ou texture déjà définie\n");
		free_tab(split);
		return (0);
	}
	game->textures[index].path = ft_strdup(split[1]);
	free_tab(split);
	return (1);
}

int	parse_textures(t_game *game, int fd)
{
	char	*line;
	int		texture_count;

	texture_count = 0;
	while ((line = get_next_line(fd)) != NULL && texture_count < 4)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strlen(line) > 0 && is_texture_identifier(line))
		{
			if (!parse_texture_line(game, line))
			{
				free(line);
				return (0);
			}
			texture_count++;
		}
		free(line);
	}
	if (line)
		free(line);
	return (1);
}

