#include "../includes/cub3d.h"

// Fonction pour gérer la fermeture propre du programme
int	close_window(t_game *param)
{
	if (param)
		free_game(param);
	exit(0);
	return (0);
}

/* Fonction de boucle principale pour tester les mouvements */
/*int game_loop(void *param)
{
	t_game	*game;
	int		x;
	int		y;

	game = (t_game *)param;
	// Mettre à jour les mouvements
	update_movements(game);
	// Afficher la position actuelle du joueur (pour test)
	//printf("Position: x=%.2f, y=%.2f | Direction: dx=%.2f, dy=%.2f\n",
			//game->player.pos_x, game->player.pos_y,
			//game->player.dir_x, game->player.dir_y);
	// Effacer l'écran
	mlx_clear_window(game->mlx, game->win);
	// Dessiner un simple carré représentant le joueur (pour test)
	x = (int)(game->player.pos_x * 20);
	y = (int)(game->player.pos_y * 20);
	mlx_string_put(game->mlx, game->win, x, y, 0xFFFFFF, "P");
	return (0);
}*/
// int game_loop(void *param)
// {
//     t_game *game = (t_game *)param;
//     mlx_clear_window(game->mlx, game->win);
//     // Test pixel rouge
//     mlx_pixel_put(game->mlx, game->win, 10, 10, 0xFF0000);
//     // Test image XPM
//     if (game->textures[0].img)
//         mlx_put_image_to_window(game->mlx, game->win, game->textures[0].img,
// 100, 100);
//     return (0);
// }
void	set_initial_direction(t_game *g)
{
	if (g->player_dir == 'N')
	{
		g->player.dir_x = 0;
		g->player.dir_y = -1; 
		g->player.plane_x = 0.66;
		g->player.plane_y = 0;
	}
	else if (g->player_dir == 'S')
	{
		g->player.dir_x = 0;
		g->player.dir_y = 1;
		g->player.plane_x = -0.66;
		g->player.plane_y = 0;
	}
	else if (g->player_dir == 'E')
	{
		g->player.dir_x = 1;
		g->player.dir_y = 0;
		g->player.plane_x = 0;
		g->player.plane_y = 0.66;
	}
	else if (g->player_dir == 'W')
	{
		g->player.dir_x = -1;
		g->player.dir_y = 0;
		g->player.plane_x = 0;
		g->player.plane_y = -0.66;
	}
}

void	init_game(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		exit_with_error(g, "MLX init failed");
	g->win_width = MAIN_WIN_WIDTH;
	g->win_height = MAIN_WIN_HEIGHT;
	g->win = mlx_new_window(g->mlx, g->win_width, g->win_height, "Cub3D");
	if (!g->win)
		exit_with_error(g, "Window creation failed");
	g->screen.img_ptr = mlx_new_image(g->mlx, g->win_width, g->win_height);
	if (!g->screen.img_ptr)
		exit_with_error(g, "Image creation failed");
	g->screen.img_data = mlx_get_data_addr(g->screen.img_ptr,
			&g->screen.bits_per_pixel, &g->screen.line_length,
			&g->screen.endian);
	for (int i = 0; i < 6; i++)
	{
		int w, h;
		if (!g->textures[i].path)
			exit_with_error(g, "Missing texture path");
		g->textures[i].img = mlx_xpm_file_to_image(g->mlx, g->textures[i].path,
				&w, &h);
		if (!g->textures[i].img)
			exit_with_error(g, "Failed to load texture");
		g->textures[i].width = w;
		g->textures[i].height = h;
		g->textures[i].img_data = mlx_get_data_addr(g->textures[i].img,
				&g->textures[i].bits_per_pixel, &g->textures[i].line_length,
				&g->textures[i].endian);
		printf("Loaded texture %d: %s (%dx%d)\n", i, g->textures[i].path, w, h);
	}
	g->move_speed = MOVE_SPEED;
	g->rot_speed = ROT_SPEED;
	ft_memset(&g->keys, 0, sizeof(t_keys));
}

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

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (!parse_game_data(&game, argc, argv))
		return (1);
	init_game(&game);
	game.player.pos_x = game.player_pos.x;
	game.player.pos_y = game.player_pos.y;
	set_initial_direction(&game);
	printf("Position du joueur sur la carte: x=%.2f, y=%.2f\n",
		game.player.pos_x, game.player.pos_y);
	printf("Direction du joueur: %c (%.2f, %.2f)\n", (int)game.player_dir,
		game.player.dir_x, game.player.dir_y);
	printf("Floor color: 0x%06X\n", game.map.floor_color);
	printf("Ceiling color: 0x%06X\n", game.map.ceiling_color);
	printf("\n\n=== INITIALISATION DES HOOKS ===\n\n");
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	printf("Hook keypress configuré\n");
	mlx_hook(game.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
