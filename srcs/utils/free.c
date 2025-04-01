#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}


void free_textures(t_game *game)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (game->textures[i].img)
            mlx_destroy_image(game->mlx, game->textures[i].img);
        if (game->textures[i].path)
            free(game->textures[i].path);
        i++;
    }
}

void    free_game(t_game *game)
{
    int i;

    if (!game)
        return;

    // Libérer la map
    if (game->map.grid)
        free_tab(game->map.grid);

    // Libérer les textures
    for (i = 0; i < 4; i++)
    {
        if (game->textures[i].img)
            mlx_destroy_image(game->mlx, game->textures[i].img);
        if (game->textures[i].path)
            free(game->textures[i].path);
    }

    // Libérer l'image principale
    if (game->screen.img_ptr)
        mlx_destroy_image(game->mlx, game->screen.img_ptr);

    // Libérer la fenêtre
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);

    // Libérer MLX
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
}
