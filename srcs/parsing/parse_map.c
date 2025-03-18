#include "cub3d.h"

int parse_map(t_game *game, int fd)
{
    char    *line;
    char    *temp_map;
    char    *temp;
    size_t  max_width;
    int     i;

    temp_map = NULL;
    max_width = 0;
    game->map.height = 0;

    if (fd < 0 || !game)
        return (0);

    ft_printf("Starting to read map...\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';
        ft_printf("Read line: %s\n", line);
        if (ft_strlen(line) > max_width)
            max_width = ft_strlen(line);
        if (!temp_map)
            temp_map = ft_strdup(line);
        else
        {
            temp = temp_map;
            temp_map = ft_strjoin(temp_map, "\n");
            free(temp);
            temp = temp_map;
            temp_map = ft_strjoin(temp_map, line);
            free(temp);
        }
        game->map.height++;
        free(line);
    }

    if (!temp_map || game->map.height == 0)
    {
        ft_putstr_fd("Error\nEmpty map file\n", 2);
        return (0);
    }

    game->map.width = (int)max_width;
    game->map.grid = ft_split(temp_map, '\n');
    free(temp_map);
    if (!game->map.grid)
        return (0);

    // Normaliser la longueur des lignes
    i = 0;
    while (i < game->map.height)
    {
        size_t current_len = ft_strlen(game->map.grid[i]);
        if (current_len < (size_t)game->map.width)
        {
            char    *new_line = malloc(game->map.width + 1);
            if (!new_line)
                return (0);
            ft_memcpy(new_line, game->map.grid[i], current_len);
            for (size_t k = current_len; k < (size_t)game->map.width; k++)
                new_line[k] = '1';
            new_line[game->map.width] = '\0';
            free(game->map.grid[i]);
            game->map.grid[i] = new_line;
            ft_printf("Normalized line %d: '%s'\n", i, game->map.grid[i]);
        }
        i++;
    }

    if (!check_map_chars(game))
    {
        ft_putstr_fd("Error\nInvalid character in map\n", 2);
        return (0);
    }
    return (1);
}

int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || 
        c == 'E' || c == 'W' || c == ' ');
}

int check_map_chars(t_game *game)
{
    int i;
    int j;
    int player_count;

    player_count = 0;
    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            if (!is_valid_char(game->map.grid[i][j]))
            {
                ft_printf("Invalid char '%c' (ASCII: %d) at [%d][%d]\n", 
                    game->map.grid[i][j], (int)game->map.grid[i][j], i, j);
                return (0);
            }
            if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S' ||
                game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
                player_count++;
            j++;
        }
        i++;
    }
    
    // Vérifier qu'il y a exactement un joueur
    if (player_count != 1)
    {
        ft_printf("Error: Map must contain exactly one player position (found %d)\n", player_count);
        return (0);
    }
    
    return (1);  // Tout est valide
}

static int is_space_or_player(char c)
{
    if(c == '0' || c == 'W' || c == 'N' || c == 'S' || c == 'E')
        return(1);
    return(0);
}

int check_map_borders(t_map *map)
{
    int i;
    int j;
    
    j = 0;
    while (j < map->width)
    {
        if (is_space_or_player(map->grid[0][j]) || 
            is_space_or_player(map->grid[map->height - 1][j]))
            return (0);
        j++;
    }

    i = 0;
    while (i < map->height)
    {
        if (is_space_or_player(map->grid[i][0]) || 
            is_space_or_player(map->grid[i][map->width - 1]))
            return (0);
        i++;
    }

    i = 1;
    while (i < map->height - 1)
    {
        j = 1;
        while (j < map->width - 1)
        {
            if (is_space_or_player(map->grid[i][j]))
            {
                if (map->grid[i-1][j] == ' ' || map->grid[i+1][j] == ' ' ||
                    map->grid[i][j-1] == ' ' || map->grid[i][j+1] == ' ')
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}