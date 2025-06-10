#include "../includes/cub3d.h"

typedef struct s_line_params
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
}			t_line_params;

void	draw_pixel(t_game *g, int px, int py, int color)
{
	int	pixel;

	if (px >= 0 && px < g->win_width && py >= 0 && py < g->win_height)
	{
		pixel = py * g->screen.line_length + px * (g->screen.bits_per_pixel
				/ 8);
		*(int *)(g->screen.img_data + pixel) = color;
	}
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
			if (x >= 0 && x < g->win_width && y >= 0 && y < g->win_height)
			{
				pixel = y * g->screen.line_length + x
					* (g->screen.bits_per_pixel / 8);
				*(int *)(g->screen.img_data + pixel) = color;
			}
			x++;
		}
		y++;
	}
}

static void	update_line_coords(t_point *start, t_line_params *params)
{
	int	e2;

	e2 = 2 * params->err;
	if (e2 >= params->dy)
	{
		params->err += params->dy;
		start->x += params->sx;
	}
	if (e2 <= params->dx)
	{
		params->err += params->dx;
		start->y += params->sy;
	}
}

static void	draw_line_pixel(t_game *g, t_point point, int color)
{
	int	pixel;

	if (point.x >= 0 && point.x < g->win_width && point.y >= 0
		&& point.y < g->win_height)
	{
		pixel = point.y * g->screen.line_length + point.x
			* (g->screen.bits_per_pixel / 8);
		*(int *)(g->screen.img_data + pixel) = color;
	}
}

void	draw_line(t_game *g, t_point start, t_point end, int color)
{
	t_line_params	params;

	params.dx = abs(end.x - start.x);
	params.dy = -abs(end.y - start.y);
	params.sx = start.x < end.x ? 1 : -1;
	params.sy = start.y < end.y ? 1 : -1;
	params.err = params.dx + params.dy;
	while (1)
	{
		draw_line_pixel(g, start, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		update_line_coords(&start, &params);
	}
}
