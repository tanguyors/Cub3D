/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:39:10 by ysuliman          #+#    #+#             */
/*   Updated: 2025/06/19 08:39:11 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (!parse_game_data(&game, argc, argv))
		exit_with_error(&game, "Erreur lors du parsing du fichier");
	init_game(&game);
	game.player.pos_x = game.player_pos_x;
	game.player.pos_y = game.player_pos_y;
	set_initial_direction(&game);
	ft_printf("Position du joueur sur la carte: x=%.2f, y=%.2f\n",
		game.player.pos_x, game.player.pos_y);
	ft_printf("Direction du joueur: %c (%.2f, %.2f)\n", game.player_dir,
		game.player.dir_x, game.player.dir_y);
	ft_printf("Floor color: 0x%06X\n", game.floor_color);
	ft_printf("Ceiling color: 0x%06X\n", game.ceiling_color);
	ft_printf("\n\n=== INITIALISATION DES HOOKS ===\n\n");
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	ft_printf("Hook keypress configuré\n");
	mlx_hook(game.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
