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

int	main(void)
{
    void	*mlx;
    void	*win;

    mlx = mlx_init();
    if (!mlx)
        return (1);
    
    win = mlx_new_window(mlx, 800, 600, "Test MLX");
    if (!win)
        return (1);

    mlx_hook(win, 17, 0, close_window, NULL);
    mlx_key_hook(win, key_hook, NULL);
    
    mlx_loop(mlx);
    return (0);
}
