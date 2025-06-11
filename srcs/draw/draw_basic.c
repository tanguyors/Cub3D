#include "../includes/cub3d.h"

void	draw_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	fill_image_circle(t_game *g, int color, t_point center, int radius)
{
	int	px;
	int	py;
	int	y;
	int	x;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				px = center.x + x;
				py = center.y + y;
				draw_pixel(g, px, py, color);
			}
			x++;
		}
		y++;
	}
}

void	fill_image_rect(t_game *g, int color, t_rect rect)
{
	int	pixel;
	int	y;
	int	x;

	y = rect.y;
	while (y < rect.y + rect.height)
	{
		x = rect.x;
		while (x < rect.x + rect.width)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
			{
				pixel = y * g->line_length + x * (g->bits_per_pixel / 8);
				*(int *)(g->addr + pixel) = color;
			}
			x++;
		}
		y++;
	}
}

void	draw_rectangle(t_game *game, t_point pos, t_point size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			draw_pixel(game, pos.x + j, pos.y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_game *game, t_point start, t_point end, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	sx = (start.x < end.x) ? 1 : -1;
	sy = (start.y < end.y) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		draw_pixel(game, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			start.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			start.y += sy;
		}
	}
}
