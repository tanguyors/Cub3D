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
    int		fd;
    int		i;
    int		player_count;

    if (argc != 2)
    {
        ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
        return (1);
    }
    ft_printf("Checking file: %s\n", argv[1]);
    if (!check_file_extension(argv[1]))
    {
        ft_putstr_fd("Error\nInvalid file extension\n", 2);
        return (1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        ft_putstr_fd("Error\nCannot open file\n", 2);
        return (1);
    }
    memset(&game, 0, sizeof(t_game));
    if (!parse_map(&game, fd))
    {
        ft_putstr_fd("Error\nFailed to parse map\n", 2);
        close(fd);
        return (1);
    }

    // Afficher la map parsée
    ft_printf("\nParsed map (%dx%d):\n", game.map.width, game.map.height);
    i = 0;
    while (i < game.map.height)
    {
        ft_printf("%s\n", game.map.grid[i]);
        i++;
    }

    // Test de validité de la map
    ft_printf("\nTesting map validity...\n");
    
    // Test des caractères
    player_count = check_map_chars(&game);
    if (player_count == 0)
    {
        ft_printf("\033[31m✗ Map is invalid: No player found!\033[0m\n");
        close(fd);
        return (1);
    }
    if (player_count > 1)
    {
        ft_printf("\033[31m✗ Map is invalid: Multiple players found (%d)!\033[0m\n", 
            player_count);
        close(fd);
        return (1);
    }
    ft_printf("\033[32m✓ Player check passed\033[0m\n");

    // Test des bordures
    if (!check_map_borders(&game.map))
    {
        ft_printf("\033[31m✗ Map is invalid: Map borders are not properly closed!\033[0m\n");
        close(fd);
        return (1);
    }
    ft_printf("\033[32m✓ Border check passed\033[0m\n");
    ft_printf("\033[32m✓ Map is valid!\033[0m\n");

    // Libération de la mémoire
    i = 0;
    while (i < game.map.height)
    {
        free(game.map.grid[i]);
        i++;
    }
    free(game.map.grid);
    close(fd);
    return (0);
}
