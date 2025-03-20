#include "cub3d.h"

static int check_args_and_file(int argc, char **argv, int *fd)
{
    if (argc != 2)
    {
        ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
        return (0);
    }
    
    ft_printf("Checking file: %s\n", argv[1]);
    if (!check_file_extension(argv[1]))
    {
        ft_putstr_fd("Error\nInvalid file extension\n", 2);
        return (0);
    }
    
    *fd = open(argv[1], O_RDONLY);
    if (*fd == -1)
    {
        ft_putstr_fd("Error\nCannot open file\n", 2);
        return (0);
    }
    
    return (1);
}

static void display_parsed_data(t_game *game)
{
    int i;
    
    // Afficher la map parsée
    ft_printf("\nParsed map (%dx%d):\n", game->map.width, game->map.height);
    i = 0;
    while (i < game->map.height)
    {
        ft_printf("%s\n", game->map.grid[i]);
        i++;
    }

    // Afficher les textures parsées
    ft_printf("\nParsed textures:\n");
    ft_printf("NO: %s\n", game->textures[0].path);
    ft_printf("SO: %s\n", game->textures[1].path);
    ft_printf("WE: %s\n", game->textures[2].path);
    ft_printf("EA: %s\n", game->textures[3].path);
    
    // Afficher les couleurs parsées
    ft_printf("\nParsed colors:\n");
    ft_printf("Floor: %#x\n", game->map.floor_color);
    ft_printf("Ceiling: %#x\n", game->map.ceiling_color);
}

int parse_game_data(t_game *game, int argc, char **argv)
{
    int fd;
    int player_count;
    
    if (!check_args_and_file(argc, argv, &fd))
        return (0);
    
    memset(game, 0, sizeof(t_game));
    
    // Parsing des textures
    if (!parse_textures(game, fd))
    {
        ft_putstr_fd("Error\nFailed to parse textures\n", 2);
        close(fd);
        return (0);
    }
    
    // Revenir au début du fichier
    lseek(fd, 0, SEEK_SET);
    
    // Parsing des couleurs
    if (!parse_colors(game, fd))
    {
        ft_putstr_fd("Error\nFailed to parse colors\n", 2);
        close(fd);
        return (0);
    }
    
    // Revenir au début du fichier pour le parsing de la map
    lseek(fd, 0, SEEK_SET);
    
    if (!parse_map(game, fd))
    {
        ft_putstr_fd("Error\nFailed to parse map\n", 2);
        close(fd);
        return (0);
    }
    
    close(fd);
    
    // Afficher les données parsées
    display_parsed_data(game);
    
    // Test de validité de la map
    ft_printf("\nTesting map validity...\n");
    
    // Test des caractères
    player_count = check_map_chars(game);
    if (player_count == 0)
    {
        ft_printf("\033[31m✗ Map is invalid: No player found!\033[0m\n");
        return (0);
    }
    if (player_count > 1)
    {
        ft_printf("\033[31m✗ Map is invalid: Multiple players found (%d)!\033[0m\n", 
            player_count);
        return (0);
    }
    ft_printf("\033[32m✓ Player check passed\033[0m\n");
    
    // Test des bordures
    if (!check_map_borders(&game->map))
    {
        ft_printf("\033[31m✗ Map is invalid: Borders not closed!\033[0m\n");
        return (0);
    }
    ft_printf("\033[32m✓ Border check passed\033[0m\n");
    
    return (1);
}
