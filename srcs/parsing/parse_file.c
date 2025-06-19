/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:36:45 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 11:10:08 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_and_process_lines(t_game *game, int fd, char **map_buffer,
		size_t *max_width)
{
	char			*line;
	int				map_started;
	int				result;
	t_pre_map_ctx	ctx;

	map_started = 0;
	ctx.game = game;
	ctx.map_started = &map_started;
	ctx.map_buffer = map_buffer;
	ctx.max_width = max_width;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!map_started)
			result = process_pre_map_line(&ctx, line);
		else
			result = process_map_line(line, map_buffer, max_width);
		free(line);
		if (result == 0)
			return (0);
		if (result == 2)
			break ;
		line = get_next_line(fd);
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
		game->map_width = (int)max_width;
		result = finalize_map(game, map_buffer);
	}
	else
		result = 0;
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
