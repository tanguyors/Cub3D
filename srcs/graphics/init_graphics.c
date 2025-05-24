#include "cub3d.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

static int	init_window(t_game *game)
{
	// Vérifier si game est valide
	if (!game)
		return (0);
	// Initialiser les dimensions de la fenêtre
	game->win_width = WINDOW_WIDTH;
	game->win_height = WINDOW_HEIGHT;
	// Initialiser MLX si pas déjà fait
	if (!game->mlx)
	{
		game->mlx = mlx_init();
		if (!game->mlx)
			return (0);
	}
	// Créer la fenêtre
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height,
			"Cub3D");
	if (!game->win)
		return (0);
	return (1);
}

static int	init_screen_image(t_game *game)
{
	// Créer l'image principale
	game->screen.img_ptr = mlx_new_image(game->mlx, game->win_width,
			game->win_height);
	if (!game->screen.img_ptr)
		return (0);
	// Récupérer l'adresse des données de l'image
	game->screen.img_data = mlx_get_data_addr(game->screen.img_ptr,
			&game->screen.bits_per_pixel, &game->screen.line_length,
			&game->screen.endian);
	// Initialiser les dimensions
	game->screen.width = game->win_width;
	game->screen.height = game->win_height;
	return (1);
}

int	load_texture(t_game *game, int index)
{
	int w, h;
	if (!game->textures[index].path)
		return (0);
	game->textures[index].img = mlx_xpm_file_to_image(game->mlx,
			game->textures[index].path, &w, &h);
	if (!game->textures[index].img)
	{
		ft_printf("Erreur chargement texture %s\n", game->textures[index].path);
		return (0);
	}
	ft_printf("Texture %d chargée : %s (%dx%d)\n", index,
		game->textures[index].path, w, h);
	game->textures[index].width = w;
	game->textures[index].height = h;
	return (1);
}

int	init_graphics(t_game *game)
{
	int	i;

	if (!init_window(game))
	{
		ft_putstr_fd("Error\nFailed to initialize window\n", 2);
		return (0);
	}
	// Initialiser l'image principale
	if (!init_screen_image(game))
	{
		ft_putstr_fd("Error\nFailed to create screen image\n", 2);
		// Nettoyer la fenêtre
		mlx_destroy_window(game->mlx, game->win);
		return (0);
	}
	i = 0;
	while (i < 6)
	{
		if (!load_texture(game, i))
			return (0);
		i++;
	}
	return (1);
}
