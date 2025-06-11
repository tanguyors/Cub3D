#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (!parse_game_data(&game, argc, argv))
		return (1);
	init_game(&game);
	game.player.pos_x = game.player_pos_x;
	game.player.pos_y = game.player_pos_y;
	set_initial_direction(&game);
	printf("Position du joueur sur la carte: x=%.2f, y=%.2f\n",
		game.player.pos_x, game.player.pos_y);
	printf("Direction du joueur: %c (%.2f, %.2f)\n", game.player_dir,
		game.player.dir_x, game.player.dir_y);
	printf("Floor color: 0x%06X\n", game.floor_color);
	printf("Ceiling color: 0x%06X\n", game.ceiling_color);
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
