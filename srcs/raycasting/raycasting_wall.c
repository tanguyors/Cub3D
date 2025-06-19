/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:38:49 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 08:38:50 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_wall_x(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	calculate_texture_x(t_game *game, t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x
			* (double)game->textures[ray->texture_index].width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = game->textures[ray->texture_index].width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = game->textures[ray->texture_index].width - ray->tex_x - 1;
}
