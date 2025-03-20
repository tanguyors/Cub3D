#include "cub3d.h"

// Fonction pour gérer la fermeture propre du programme
int	close_window(void *param)
{
    (void)param;  // Indiquer que le paramètre est intentionnellement non utilisé
    exit(0);
    return (0);
}

// Fonction pour gérer les touches du clavier
int	key_hook(int keycode, void *param)
{
    (void)param;  // Indiquer que le paramètre est intentionnellement non utilisé
    if (keycode == 65307) // ESC key
        exit(0);
    return (0);
}

int	main(int argc, char **argv)
{
    t_game game;

    // Parsing des données du jeu
    if (!parse_game_data(&game, argc, argv))
        return (1);

    // Initialisation de la MLX
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
        // Libérer la mémoire allouée
        return (1);
    }

    // Création de la fenêtre
    game.win = mlx_new_window(game.mlx, 800, 600, "cub3D");
    if (!game.win)
    {
        ft_putstr_fd("Error\nFailed to create window\n", 2);
        // Libérer la mémoire allouée
        return (1);
    }

    // Configuration des hooks pour les événements
    mlx_hook(game.win, 17, 0, close_window, &game); // Hook pour la fermeture de la fenêtre
    mlx_key_hook(game.win, key_hook, &game);        // Hook pour les touches du clavier

    // Boucle principale
    mlx_loop(game.mlx);

    return (0);
}
