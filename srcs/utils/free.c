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

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		if (game->textures[i].path)
			free(game->textures[i].path);
		i++;
	}
}

void	free_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->map.grid)
		free_tab(game->map.grid);
	for (i = 0; i < 6; i++)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		if (game->textures[i].path)
			free(game->textures[i].path);
	}
	if (game->screen.img_ptr)
		mlx_destroy_image(game->mlx, game->screen.img_ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
