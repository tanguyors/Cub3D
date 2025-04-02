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
int game_loop(void *param)
{
    t_game *game;
    
    game = (t_game *)param;
    
    // Mettre à jour les mouvements
    update_movements(game);
    
    // Afficher la position actuelle du joueur (pour test)
    printf("Position: x=%.2f, y=%.2f | Direction: dx=%.2f, dy=%.2f\n",
           game->player.pos_x, game->player.pos_y,
           game->player.dir_x, game->player.dir_y);
    
    // Effacer l'écran
    mlx_clear_window(game->mlx, game->win);
    
    // Dessiner un simple carré représentant le joueur (pour test)
    int x = (int)(game->player.pos_x * 20);
    int y = (int)(game->player.pos_y * 20);
    mlx_string_put(game->mlx, game->win, x, y, 0xFFFFFF, "P");
    
    return (0);
}

int main(int argc, char **argv)
{
    t_game game;
    
    // Initialisation
    ft_memset(&game, 0, sizeof(t_game));
    
    // Parser les données du jeu
    if (parse_game_data(&game, argc, argv) == -1)
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
        game.player.dir_x = 1.0;  // Regardant vers l'est par défaut
        game.player.dir_y = 0.0;
        game.player.plane_x = 0.0;
        game.player.plane_y = 0.66;
    }
    
    // Configurer les hooks pour les événements
    printf("\n\n=== INITIALISATION DES HOOKS ===\n\n");
    mlx_key_hook(game.win, handle_keypress, &game);
    printf("Hook keypress configuré\n");
    mlx_hook(game.win, 3, 1L<<1, handle_keyrelease, &game); // Relâchement de touches
    mlx_hook(game.win, 17, 0, close_window, &game);         // Fermeture fenêtre
    
    // Configurer la boucle principale
    mlx_loop_hook(game.mlx, game_loop, &game);
    
    // Lancer la boucle MLX
    mlx_loop(game.mlx);
    
    // Libérer les ressources
    free_game(&game);
    
    return (0);
}
