#include "cub3d.h"

/* Check collision */
int check_collision(t_game *game, double new_x, double new_y)
{
    (void)game;   // Indique que ces paramètres ne sont pas utilisés
    (void)new_x;  // intentionnellement 
    (void)new_y;
    return (0);   // Désactiver temporairement les collisions pour tester
}

/* Mouvement vers l'avant */
void move_forward(t_game *game)
{
    double new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
    double new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
    
    if (!check_collision(game, new_x, game->player.pos_y))
        game->player.pos_x = new_x;
    if (!check_collision(game, game->player.pos_x, new_y))
        game->player.pos_y = new_y;
}

/* Mouvement vers l'arrière */
void move_backward(t_game *game)
{
    double new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
    double new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
    
    if (!check_collision(game, new_x, game->player.pos_y))
        game->player.pos_x = new_x;
    if (!check_collision(game, game->player.pos_x, new_y))
        game->player.pos_y = new_y;
}

/* Mouvement latéral gauche */
void move_left(t_game *game)
{
    // Perpendiculaire à la direction = (-dir_y, dir_x)
    double new_x = game->player.pos_x - game->player.dir_y * MOVE_SPEED;
    double new_y = game->player.pos_y + game->player.dir_x * MOVE_SPEED;
    
    if (!check_collision(game, new_x, game->player.pos_y))
        game->player.pos_x = new_x;
    if (!check_collision(game, game->player.pos_x, new_y))
        game->player.pos_y = new_y;
}

/* Mouvement latéral droit */
void move_right(t_game *game)
{
    // Perpendiculaire à la direction = (dir_y, -dir_x)
    double new_x = game->player.pos_x + game->player.dir_y * MOVE_SPEED;
    double new_y = game->player.pos_y - game->player.dir_x * MOVE_SPEED;
    
    if (!check_collision(game, new_x, game->player.pos_y))
        game->player.pos_x = new_x;
    if (!check_collision(game, game->player.pos_x, new_y))
        game->player.pos_y = new_y;
}

/* Rotation vers la gauche */
void rotate_left(t_game *game)
{
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;
    
    // Rotation de la direction
    game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - game->player.dir_y * sin(-ROT_SPEED);
    game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y * cos(-ROT_SPEED);
    
    // Rotation du plan caméra
    game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - game->player.plane_y * sin(-ROT_SPEED);
    game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y * cos(-ROT_SPEED);
}

/* Rotation vers la droite */
void rotate_right(t_game *game)
{
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;
    
    // Rotation de la direction
    game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
    game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y * cos(ROT_SPEED);
    
    // Rotation du plan caméra
    game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - game->player.plane_y * sin(ROT_SPEED);
    game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y * cos(ROT_SPEED);
}
