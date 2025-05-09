#include <cub3d.h>

void	fill_image_circle(t_game *g, int color, t_point center, int radius)
{
	int	px;
	int	py;
	int	pixel;

	for (int y = -radius; y <= radius; y++)
	{
		for (int x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
			{
				px = center.x + x;
				py = center.y + y;
				if (px >= 0 && px < g->win_width && py >= 0
					&& py < g->win_height)
				{
					pixel = py * g->screen.line_length + px
						* (g->screen.bits_per_pixel / 8);
					*(int *)(g->screen.img_data + pixel) = color;
				}
			}
		}
	}
}

void	fill_image_rect(t_game *g, int color, t_rect rect)
{
	int	pixel;

	for (int y = rect.y; y < rect.y + rect.height; y++)
	{
		for (int x = rect.x; x < rect.x + rect.width; x++)
		{
			if (x >= 0 && x < g->win_width && y >= 0 && y < g->win_height)
			{
				pixel = y * g->screen.line_length + x
					* (g->screen.bits_per_pixel / 8);
				*(int *)(g->screen.img_data + pixel) = color;
			}
		}
	}
}
void draw_wall_tile(t_game *g, int grid_x, int grid_y)
{
    t_rect wall_rect = {
        .x = grid_x * TILE_SIZE,
        .y = grid_y * TILE_SIZE,
        .width = TILE_SIZE,
        .height = TILE_SIZE};
    fill_image_rect(g, 0x505050, wall_rect);
}

void	draw_map(t_game *g)
{
	// Base map color (non-walls)
	fill_image_rect(g, 0x202020, (t_rect){0, 0, g->win_width, g->win_height});
	// Draw walls
	for (int y = 0; y < g->map.height; y++)
	{
		for (int x = 0; x < g->map.width; x++)
		{
			if (g->map.grid[y][x] == '1')
			{
				draw_wall_tile(g, x, y);
			}
		}
	}
}

void	draw_line(t_game *g, t_point start, t_point end, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	pixel;
	int	e2;

	dx = abs(end.x - start.x);
	dy = -abs(end.y - start.y);
	sx = start.x < end.x ? 1 : -1;
	sy = start.y < end.y ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		if (start.x >= 0 && start.x < g->win_width && start.y >= 0
			&& start.y < g->win_height)
		{
			pixel = start.y * g->screen.line_length + start.x
				* (g->screen.bits_per_pixel / 8);
			*(int *)(g->screen.img_data + pixel) = color;
		}
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			start.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			start.y += sy;
		}
	}
}

void draw_player(t_game *g)
{
    // Convert player position to screen coordinates
    int px = g->player.pos_x * TILE_SIZE;
    int py = g->player.pos_y * TILE_SIZE;
    
    // Draw player circle (5x5 pixels)
    fill_image_circle(g, 0xFF0000, (t_point){px, py}, 3);

    // Draw direction vector (20px length)
    t_point dir_end = {
        px + g->player.dir_x * 20,
        py + g->player.dir_y * 20
    };
    draw_line(g, (t_point){px, py}, dir_end, 0x00FF00);
}
