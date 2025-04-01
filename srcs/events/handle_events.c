#include "cub3d.h"

int    handle_keypress(int keycode, t_game *game)
{
    if (!game)
        return (0);
    ft_printf("Touche pressée: %d\n", keycode);
    if (keycode == KEY_ESC)
        close_window(game);
    else if (keycode == KEY_W)
        game->keys.w_pressed = 1;
    else if (keycode == KEY_S)
        game->keys.s_pressed = 1;
    else if (keycode == KEY_A)
        game->keys.a_pressed = 1;
    else if (keycode == KEY_D)
        game->keys.d_pressed = 1;
    else if (keycode == KEY_LEFT)
        game->keys.left_pressed = 1;
    else if (keycode == KEY_RIGHT)
        game->keys.right_pressed = 1;
    return (0);
}

int    handle_keyrelease(int keycode, t_game *game)
{
    if (!game)
        return (0);
    if (keycode == KEY_W)
        game->keys.w_pressed = 0;
    else if (keycode == KEY_S)
        game->keys.s_pressed = 0;
    else if (keycode == KEY_A)
        game->keys.a_pressed = 0;
    else if (keycode == KEY_D)
        game->keys.d_pressed = 0;
    else if (keycode == KEY_LEFT)
        game->keys.left_pressed = 0;
    else if (keycode == KEY_RIGHT)
        game->keys.right_pressed = 0;
    return (0);
}
