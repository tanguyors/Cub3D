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
	// Use your parser's stored initial direction
	if (g->player_dir == 'N')
	{
		g->player.dir_x = 0;
		g->player.dir_y = -1; // Y increases downward
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
	// 1. Initialize MLX connection
	g->mlx = mlx_init();
	if (!g->mlx)
		exit_with_error(g, "MLX init failed");
	// 2. Create window
	g->win = mlx_new_window(g->mlx, g->win_width, g->win_height, "Cub3D");
	if (!g->win)
		exit_with_error(g, "Window creation failed");
	// 3. Initialize screen buffer
	g->screen.img_ptr = mlx_new_image(g->mlx, g->win_width, g->win_height);
	if (!g->screen.img_ptr)
		exit_with_error(g, "Image creation failed");
	// 4. Get image data address
	g->screen.img_data = mlx_get_data_addr(g->screen.img_ptr,
			&g->screen.bits_per_pixel, &g->screen.line_length,
			&g->screen.endian);
	// 5. Set initial direction vectors
	set_initial_direction(g); // Critical for raycasting later
}

void	render_2d(t_game *g)
{
	draw_map(g);
	draw_player(g);
	mlx_put_image_to_window(g->mlx, g->win, g->screen.img_ptr, 0, 0);
}

int	game_loop(t_game *game)
{
	// Handle continuous movement
	if (game->keys.w)
		move_forward(game);
	if (game->keys.s)
		move_backward(game);
	if (game->keys.a)
		move_left(game);
	if (game->keys.d)
		move_right(game);
	if (game->keys.left)
		rotate_left(game);
	if (game->keys.right)
		rotate_right(game);
	// Clear and redraw frame
	render_2d(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	// Initialisation
	ft_memset(&game, 0, sizeof(t_game));
	// Parser les données du jeu
	if (!parse_game_data(&game, argc, argv))
		return (1);
	// Initialiser les graphiques
	if (init_graphics(&game) == -1)
		return (1);
	// Après parse_game_data
	printf("Position du joueur sur la carte: x=%.2f, y=%.2f\n",
		game.player_pos.x, game.player_pos.y);
	// Initialiser la structure du joueur
	game.player.pos_x = game.player_pos.x;
	game.player.pos_y = game.player_pos.y;
	// Définir une direction par défaut si nécessaire
	if (game.player.dir_x == 0 && game.player.dir_y == 0)
	{
		game.player.dir_x = 1.0; // Regardant vers l'est par défaut
		game.player.dir_y = 0.0;
		game.player.plane_x = 0.0;
		game.player.plane_y = 0.66;
	}
	init_game(&game);
	// Configurer les hooks pour les événements
	printf("\n\n=== INITIALISATION DES HOOKS ===\n\n");
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	printf("Hook keypress configuré\n");
	mlx_hook(game.win, 3, 1L << 1, handle_keyrelease, &game);
	// Relâchement de touches
	mlx_hook(game.win, 17, 0, close_window, &game);
	// Fermeture fenêtre
	// Configurer la boucle principale
	mlx_loop_hook(game.mlx, game_loop, &game);
	// Lancer la boucle MLX
	mlx_loop(game.mlx);
	// Libérer les ressources
	free_game(&game);
	return (0);
}
