#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

/* Key codes */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* Movement and rotation speeds */
# define MOVE_SPEED 0.15
# define ROT_SPEED 0.08

/* Pixels per grid cell */
# define TILE_SIZE 32
/* Prevents wall clipping */
# define PLAYER_RADIUS 0.2

/* Window dimensions */
# define MAIN_WIN_WIDTH 1920
# define MAIN_WIN_HEIGHT 1080
# define MINIMAP_WIDTH 300
# define MINIMAP_HEIGHT 300

/* Structure pour les coordonnées */
typedef struct s_pos
{
	double		x;
	double		y;
}				t_pos;

/* Structure pour les textures */
typedef struct s_texture
{
	char		*path;
	void		*img;
	char		*img_data;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_texture;

/* Structure pour la map */
typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			floor_color;
	int			ceiling_color;
}				t_map;

typedef struct s_img
{
	void *img_ptr;      // Pointeur vers l'image MLX
	char *img_data;     // Pointeur vers les données de l'image (pixels)
	int bits_per_pixel; // Nombre de bits par pixel (généralement 32)
	int line_length;    // Nombre d'octets par ligne
	int endian;         // Format des couleurs (petit ou grand-endian)
	int width;          // Largeur de l'image en pixels
	int height;         // Hauteur de l'image en pixels
}				t_img;

/* Structure pour l'état des touches */
typedef struct s_player
{
	double pos_x;   // Position X du joueur
	double pos_y;   // Position Y du joueur
	double dir_x;   // Vecteur direction X
	double dir_y;   // Vecteur direction Y
	double plane_x; // Plan caméra X
	double plane_y; // Plan caméra Y
}				t_player;

typedef struct s_keys
{
	int w;     // Avancer
	int s;     // Reculer
	int a;     // Gauche
	int d;     // Droite
	int left;  // Rotation gauche
	int right; // Rotation droite
	int esc;   // Quitter
}				t_keys;

/* Structure principale */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_texture textures[4]; // NO, SO, WE, EA (floor and ceiling use colors)
	t_pos		player_pos;
	t_player	player;
	char		player_dir;
	int win_width;     // largeur de la window
	int win_height;    // hauteur de la window
	t_img screen;      // image principal pour le rendu
	t_keys keys;       // état des touches
	double move_speed; // vitesse de déplacement
	double rot_speed;  // vitesse de rotation
}				t_game;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_rect
{
	int			x;
	int			y;
	int			width;
	int			height;
}				t_rect;

/* Parsing functions */
int				check_file_extension(char *filename);
int				check_file_access(char *filename);
int				parse_map(t_game *game, int fd);
int				is_valid_char(char c);
int				check_map_borders(t_map *map);
int				count_player(t_map *map);
int				check_map_chars(t_game *game);
int				parse_textures(t_game *game, int fd);
int				parse_colors(t_game *game, int fd);
void			free_tab(char **tab);
int				parse_game_data(t_game *game, int argc, char **argv);
int				is_texture_identifier(char *line);
int				is_color_identifier(char *line);
int				init_graphics(t_game *game);
int				parse_texture_line(t_game *game, char *line);
int				parse_texture(t_game *game, char *line);

/* Events functions */
int				handle_keypress(int keycode, t_game *game);
int				handle_keyrelease(int keycode, t_game *game);

int				close_window(t_game *param);
void			free_game(t_game *game);
void			free_textures(t_game *game);

// Fonctions de mouvement
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);

// Fonctions de rotation
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);

// Fonction de vérification de collision
int				check_collision(t_game *game, double new_x, double new_y);

// Ajouter la déclaration de update_movements
void			update_movements(t_game *game);

int				is_in_circle(int x, int y, int center_x, int center_y,
					int radius);
void			draw_map(t_game *g);
void			draw_player(t_game *g);
int				exit_with_error(t_game *g, const char *msg);

/* Drawing functions */
void			draw_pixel(t_game *g, int px, int py, int color);
void			fill_image_circle(t_game *g, int color, t_point center,
					int radius);
void			fill_image_rect(t_game *g, int color, t_rect rect);
void			draw_line(t_game *g, t_point start, t_point end, int color);
void			draw_wall_tile(t_game *g, int grid_x, int grid_y);

/* Raycasting struct */
typedef struct s_ray_vars
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
	int			tex_y;
}				t_ray_vars;

/* Raycasting functions */
void			cast_ray(t_game *g, int x);
void			render_3d(t_game *g);
void			draw_floor_ceiling(t_game *g);
void			calculate_wall_height(t_game *g, t_ray_vars *vars);
void			calculate_texture_coords(t_game *g, t_ray_vars *vars);
void			draw_wall_stripe(t_game *g, t_ray_vars *vars, int x);

/* Map parsing functions */
int				init_map_reading(t_game *game, int fd);
char			*handle_line(char *line, char *temp_map, size_t *max_width);
char			*read_map_lines(t_game *game, int fd, size_t *max_width);
int				normalize_line(t_game *game, int i);
int				normalize_map_lines(t_game *game);
int				parse_player_position(t_game *game);
int				is_valid_char(char c);
int				check_map_chars(t_game *game);
int				is_space_or_player(char c);
int				check_horizontal_borders(t_map *map);
int				check_vertical_borders(t_map *map);
int				check_spaces_around(t_map *map);
int				check_map_borders(t_map *map);
int				parse_map(t_game *game, int fd);
int				parse_map_content(t_game *game, char *map_content);

/* New parsing functions */
int				parse_color_line(t_game *game, char *line);
int				process_pre_map_line(t_game *game, char *line, int *map_started,
					char **map_buffer, size_t *max_width);
int				process_map_line(char *line, char **map_buffer,
					size_t *max_width);
int				handle_map_line(char *line, char **map_buffer,
					size_t *max_width);
int				finalize_map(t_game *game, char *map_buffer);
int				parse_textures_and_colors(t_game *game, char *line);
int				read_and_process_lines(t_game *game, int fd, char **map_buffer,
					size_t *max_width);
int				parse_file_single_pass(t_game *game, const char *filename);
int				is_map_line(char *line);

void			init_game(t_game *g);
void			set_initial_direction(t_game *g);
int				game_loop(t_game *game);
void			render_minimap(t_game *g);

int				get_texture_index(char *identifier);
int				validate_texture_parts(char **parts);
int				handle_texture_path(t_game *game, char **parts, int index);
int				parse_texture(t_game *game, char *line);
int				check_floor_ceiling_texture(char *trimmed);
int				parse_texture_if_valid(t_game *game, char *trimmed,
					int *texture_count);
int				process_texture_line(t_game *game, char *line,
					int *texture_count);

#endif
