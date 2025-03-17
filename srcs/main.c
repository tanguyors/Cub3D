#include "cub3d.h"

// Fonction pour gérer la fermeture propre du programme
int	close_window(void *param)
{
    (void)param;
    exit(0);
    return (0);
}

// Fonction pour gérer les touches du clavier
int	key_hook(int keycode, void *param)
{
    (void)param;
    if (keycode == 65307) // ESC key
        exit(0);
    return (0);
}

int	main(int argc, char **argv)
{
    t_game	game;

    if (argc != 2)
    {
        ft_putstr_fd("Error\nUsage: ./cub3D map_file.cub\n", 2);
        return (1);
    }

    if (!check_file_extension(argv[1]))
    {
        ft_putstr_fd("Error\nInvalid file extension. Must be .cub\n", 2);
        return (1);
    }

    if (!check_file_access(argv[1]))
    {
        ft_putstr_fd("Error\nCannot access file\n", 2);
        return (1);
    }

    memset(&game, 0, sizeof(t_game));
    // ... reste du code ...
    return (0);
}
