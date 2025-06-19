/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_borders_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:10:00 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 11:10:03 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	trim_trailing_spaces_len(const char *line)
{
	int	len;

	len = ft_strlen(line);
	while (len > 0 && line[len - 1] == ' ')
		len--;
	return (len);
}

static int	check_top_border(char **map)
{
	int	j;
	int	len;

	len = trim_trailing_spaces_len(map[0]);
	j = 0;
	while (j < len)
	{
		if (map[0][j] != '1')
		{
			ft_printf("Error: Invalid top border at (0, %d): %c\n", j,
				map[0][j]);
			return (0);
		}
		j++;
	}
	return (1);
}

static int	check_bottom_border(char **map, int map_height)
{
	int	j;
	int	len;

	len = trim_trailing_spaces_len(map[map_height - 1]);
	j = 0;
	while (j < len)
	{
		if (map[map_height - 1][j] != '1')
		{
			ft_printf("Error: Invalid bottom border at (%d, %d): %c\n",
				map_height - 1, j, map[map_height - 1][j]);
			return (0);
		}
		j++;
	}
	return (1);
}

static int	check_side_borders(char **map, int map_height)
{
	int	i;
	int	len;

	i = 1;
	while (i < map_height - 1)
	{
		len = trim_trailing_spaces_len(map[i]);
		if (len > 0 && map[i][0] != '1')
		{
			ft_printf("Error: Invalid left border at (%d, 0): %c\n", i,
				map[i][0]);
			return (0);
		}
		if (len > 1 && map[i][len - 1] != '1')
		{
			ft_printf("Error: Invalid right border at (%d, %d): %c\n", i, len
				- 1, map[i][len - 1]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_raw_map_borders(char **map, int map_height)
{
	if (!check_top_border(map))
		return (0);
	if (!check_bottom_border(map, map_height))
		return (0);
	if (!check_side_borders(map, map_height))
		return (0);
	return (1);
}
