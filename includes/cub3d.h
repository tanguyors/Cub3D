#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"

/* Key codes */
# define KEY_ESC    65307
# define KEY_W      119
# define KEY_A      97
# define KEY_S      115
# define KEY_D      100
# define KEY_LEFT   65361
# define KEY_RIGHT  65363

/* Movement and rotation speeds */
# define MOVE_SPEED 0.1
# define ROT_SPEED  0.05

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


typedef struct s_img
{
    void    *img_ptr;          // Pointeur vers l'image MLX
    char    *img_data;         // Pointeur vers les données de l'image (pixels)
    int     bits_per_pixel;    // Nombre de bits par pixel (généralement 32)
    int     line_length;       // Nombre d'octets par ligne
    int     endian;           // Format des couleurs (petit ou grand-endian)
    int     width;            // Largeur de l'image en pixels
    int     height;           // Hauteur de l'image en pixels            
}   t_img;

/* Structure pour l'état des touches */
typedef struct s_player
{
    double  pos_x;      // Position X du joueur
    double  pos_y;      // Position Y du joueur
    double  dir_x;      // Vecteur direction X
    double  dir_y;      // Vecteur direction Y
    double  plane_x;    // Plan caméra X
    double  plane_y;    // Plan caméra Y
}   t_player;

typedef struct s_keys
{
    int     w;          // Avancer
    int     s;          // Reculer
    int     a;          // Gauche
    int     d;          // Droite
    int     left;       // Rotation gauche
    int     right;      // Rotation droite
    int     esc;        // Quitter
}   t_keys;


/* Structure principale */
typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_map       map;
    t_texture   textures[4]; // NO, SO, WE, EA
    t_pos       player_pos;
    double      player_dir;
    int         win_width;        // largeur de la window
    int         win_height;       // hauteur de la window
    t_img       screen;          // image principal pour le rendu
    t_keys      keys;           // état des touches
    double      move_speed;     // vitesse de déplacement
    double      rot_speed;      // vitesse de rotation
}   t_game;

/* Parsing functions */
int		check_file_extension(char *filename);
int		check_file_access(char *filename);
int     parse_map(t_game *game, int fd);
int     is_valid_char(char c);
int     check_map_borders(t_map *map);
int     count_player(t_map *map);
int     check_map_chars(t_game *game);
int		parse_textures(t_game *game, int fd);
int		parse_colors(t_game *game, int fd);
void	free_tab(char **tab);
int parse_game_data(t_game *game, int argc, char **argv);
int is_texture_identifier(char *line);
int is_color_identifier(char *line);
int init_graphics(t_game *game);

/* Events functions */
int     handle_keypress(int keycode, t_game *game);
int     handle_keyrelease(int keycode, t_game *game);

int     close_window(t_game *param);
void    free_game(t_game *game);
void free_textures(t_game *game);

// Fonctions de mouvement
void move_forward(t_game *game);
void move_backward(t_game *game);
void move_left(t_game *game);
void move_right(t_game *game);

// Fonctions de rotation
void rotate_left(t_game *game);
void rotate_right(t_game *game);

// Fonction de vérification de collision
int check_collision(t_game *game, double new_x, double new_y);

#endif
