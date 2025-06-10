#include "cub3d.h"

int	parse_texture_line(t_game *game, char *line)
{
	if (!is_texture_identifier(line))
		return (0);
	return (parse_texture(game, line));
}
