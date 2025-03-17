#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"

/* Structure pour les coordonnées */
typedef struct s_pos
{
    double	x;
    double	y;
}   t_pos;

/* Structure pour les textures */
typedef struct s_texture
{
    void	*img;
    char	*path;
    int		width;
    int		height;
}   t_texture;

/* Structure pour la map */
typedef struct s_map
{
    char	**grid;
    int		width;
    int		height;
    int		floor_color;
    int		ceiling_color;
}   t_map;

/* Structure principale */
typedef struct s_game
{
    void		*mlx;
    void		*win;
    t_map		map;
    t_texture	textures[4]; // NO, SO, WE, EA
    t_pos		player_pos;
    double		player_dir;
    // Autres variables à ajouter selon les besoins
}   t_game;

/* Parsing functions */
int		check_file_extension(char *filename);
int		check_file_access(char *filename);
int     parse_textures(t_game *game, int fd);
int     parse_colors(t_game *game, int fd);
int     parse_map(t_game *game, int fd);

#endif
