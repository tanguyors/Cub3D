#include "cub3d.h"

/* Fonction pour gérer l'appui sur une touche */
int handle_keypress(int keycode, t_game *game)
{
    printf("Touche pressée: %d\n", keycode);
    if (keycode == KEY_W)
    {
        printf("W pressée\n");
        game->keys.w = 1;
    }
    else if (keycode == KEY_A)
    {
        printf("A pressée\n");
        game->keys.a = 1;
    }
    else if (keycode == KEY_S)
    {
        printf("S pressée\n");
        game->keys.s = 1;
    }
    else if (keycode == KEY_D)
    {
        printf("D pressée\n");
        game->keys.d = 1;
    }
    else if (keycode == KEY_ESC)
        close_window(game);
    else if (keycode == KEY_LEFT)
        game->keys.left = 1;
    else if (keycode == KEY_RIGHT)
        game->keys.right = 1;
    return (0);
}

/* Fonction pour gérer le relâchement d'une touche */
int handle_keyrelease(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->keys.w = 0;
    else if (keycode == KEY_S)
        game->keys.s = 0;
    else if (keycode == KEY_A)
        game->keys.a = 0;
    else if (keycode == KEY_D)
        game->keys.d = 0;
    else if (keycode == KEY_LEFT)
        game->keys.left = 0;
    else if (keycode == KEY_RIGHT)
        game->keys.right = 0;
    return (0);
}

/* Fonction pour mettre à jour la position du joueur à chaque frame */
void update_movements(t_game *game)
{
   // printf("Keys: W=%d S=%d A=%d D=%d LEFT=%d RIGHT=%d\n", 
          // game->keys.w, game->keys.s, game->keys.a, 
           //game->keys.d, game->keys.left, game->keys.right);
    
    //printf("Position avant: x=%.2f, y=%.2f | Direction: dx=%.2f, dy=%.2f\n",
          // game->player.pos_x, game->player.pos_y,
           //game->player.dir_x, game->player.dir_y);
    
    if (game->keys.w)
    {
        printf("Touche W pressée - Avancer\n");
        move_forward(game);
    }
    if (game->keys.s)
    {
        printf("Touche S pressée - Reculer\n");
        move_backward(game);
    }
    if (game->keys.a)
    {
        printf("Touche A pressée - Gauche\n");
        move_left(game);
    }
    if (game->keys.d)
    {
        printf("Touche D pressée - Droite\n");
        move_right(game);
    }
    if (game->keys.left)
    {
        printf("Touche LEFT pressée - Rotation gauche\n");
        rotate_left(game);
    }
    if (game->keys.right)
    {
        printf("Touche RIGHT pressée - Rotation droite\n");
        rotate_right(game);
    }
    
    //printf("Position après: x=%.2f, y=%.2f | Direction: dx=%.2f, dy=%.2f\n",
           //game->player.pos_x, game->player.pos_y,
         //  game->player.dir_x, game->player.dir_y);
}
