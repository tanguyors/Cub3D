#include "cub3d.h"

// Fonction pour gérer la fermeture propre du programme
int	close_window(t_game *param)
{
    if (param)
        free_game(param);
    exit(0);
    return (0);
}


int	main(int argc, char **argv)
{
    t_game game;

    // Parsing des données du jeu
    if (!parse_game_data(&game, argc, argv))
        return (1);

    // Initialisation des graphiques
    if (!init_graphics(&game))
    {
        free_game(&game);
        return (1);
    }

    // Configuration des hooks pour les événements
    mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);
    mlx_hook(game.win, 3, 1L<<1, handle_keyrelease, &game);
    mlx_hook(game.win, 17, 0, close_window, &game);
    mlx_loop(game.mlx);
    free_game(&game);
    return (0);
}
