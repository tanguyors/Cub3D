/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_content_pre.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:40:00 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 09:54:14 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_textures_and_colors(t_game *game, char *line);
int	handle_map_line(char *line, char **map_buffer, size_t *max_width);

int	process_pre_map_line_ctx(t_pre_map_ctx *ctx, char *line);

int	process_pre_map_line(t_pre_map_ctx *ctx, char *line)
{
	return (process_pre_map_line_ctx(ctx, line));
}

int	process_pre_map_line_ctx(t_pre_map_ctx *ctx, char *line)
{
	if (is_texture_identifier(line) || is_color_identifier(line))
	{
		if (!parse_textures_and_colors(ctx->game, line))
			return (0);
	}
	else if (is_map_line(line))
	{
		*(ctx->map_started) = 1;
		if (!handle_map_line(line, ctx->map_buffer, ctx->max_width))
			return (0);
	}
	return (1);
}
