/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:37:17 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 11:10:00 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_map_reading(t_game *game, int fd)
{
	if (fd < 0 || !game)
		return (0);
	game->map_height = 0;
	ft_printf("Starting to read map...\n");
	return (1);
}

char	*handle_line(char *line, char *temp_map, size_t *max_width)
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

static void	process_map_line_read(char *line, t_mapreadctx *ctx)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (is_map_line(line))
	{
		*(ctx->map_started) = 1;
		*(ctx->temp_map) = handle_line(line, *(ctx->temp_map), ctx->max_width);
		ctx->game->map_height++;
	}
}

char	*read_map_lines(t_game *game, int fd, size_t *max_width)
{
	char			*line;
	char			*temp_map;
	int				map_started;
	t_mapreadctx	ctx;

	map_started = 0;
	temp_map = NULL;
	*max_width = 0;
	ctx.temp_map = &temp_map;
	ctx.max_width = max_width;
	ctx.game = game;
	ctx.map_started = &map_started;
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_map_line_read(line, &ctx);
		if (!is_map_line(line) && map_started)
		{
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (temp_map);
}
