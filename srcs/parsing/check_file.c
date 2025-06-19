/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:36:12 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 12:20:33 by torsini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_extension(char *filename)
{
	char	*dot;

	if (!filename)
		return (0);
	dot = ft_strrchr(filename, '.');
	if (!dot)
		return (0);
	if (ft_strncmp(dot, ".cub", 5) != 0)
		return (0);
	return (1);
}
