#include "cub3d.h"

void	render_minimap(t_game *g)
{
	int	orig_width;
	int	orig_height;

	orig_width = g->win_width;
	orig_height = g->win_height;
	g->win_width = MINIMAP_WIDTH;
	g->win_height = MINIMAP_HEIGHT;
	draw_map(g);
	draw_player(g);
	g->win_width = orig_width;
	g->win_height = orig_height;
}

int	game_loop(t_game *game)
{
	update_movements(game);
	fill_image_rect(game, game->map.ceiling_color, (t_rect){0, 0,
		game->win_width, game->win_height / 2});
	fill_image_rect(game, game->map.floor_color, (t_rect){0, game->win_height
		/ 2, game->win_width, game->win_height / 2});
	render_3d(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img_ptr, 0, 0);
	return (0);
}
