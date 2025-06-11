#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define TILE_SIZE 64
# define PLAYER_RADIUS 5
# define PLAYER_DIR_LENGTH 20
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.1
# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200

// Key codes
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

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

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*path;
}				t_texture;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_ray
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
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			texture_index;
}				t_ray;

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
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			tex_num;
	double		step;
	double		tex_pos;
}				t_ray_vars;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_texture	textures[4];
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	char		player_dir;
	double		player_pos_x;
	double		player_pos_y;
	t_keys		keys;
}				t_game;

// Basic drawing functions
void			draw_pixel(t_game *game, int x, int y, int color);
void			draw_rectangle(t_game *game, t_point pos, t_point size,
					int color);
void			draw_line(t_game *game, t_point start, t_point end, int color);
void			draw_vertical_line(t_game *game, int x, int start, int end,
					t_ray *ray);
int				is_in_circle(t_point point, t_point center, int radius);
void			fill_image_circle(t_game *g, int color, t_point center,
					int radius);
void			fill_image_rect(t_game *g, int color, t_rect rect);

// Map drawing functions
void			draw_map_background(t_game *game);
void			draw_map_grid(t_game *game);
void			draw_map_player(t_game *game);
void			draw_map_ray(t_game *game, t_ray *ray);
void			draw_map_wall(t_game *game, t_ray *ray, int x);
void			draw_map(t_game *game);
void			draw_map_rays(t_game *game);

// Player drawing functions
void			draw_player(t_game *game);

// Raycasting functions
void			calculate_ray(t_game *game, t_ray *ray, int x);
void			calculate_wall_x(t_game *game, t_ray *ray);
void			calculate_texture_x(t_game *game, t_ray *ray);
void			render_wall(t_game *game, t_ray *ray, int x);

// Movement functions
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);
int				check_movement(t_game *game, double new_x, double new_y);

// Game initialization functions
int				init_game(t_game *game);
int				init_textures(t_game *game);
void			init_player(t_game *game);

// Map parsing functions
int				parse_map(t_game *game, int fd);
int				parse_map_line(t_game *game, char *line);
int				parse_player_position(t_game *game);
int				validate_map_borders(t_game *game);
int				validate_map_spaces(t_game *game);
int				validate_map_chars(t_game *game);
int				init_map_reading(t_game *game, int fd);
char			*read_map_lines(t_game *game, int fd, size_t *max_width);
int				normalize_map_lines(t_game *game);
int				normalize_line(t_game *game, int i);

// Texture parsing functions
int				parse_textures(t_game *game, int fd);
int				parse_colors(t_game *game, int fd);

// Utility functions
void			free_map(char **map, int height);
void			free_textures(t_game *game);
void			free_game(t_game *game);
int				check_file_extension(char *filename);
int				check_file_exists(char *filename);
int				check_file_permissions(char *filename);
int				check_file_content(char *filename);
void			free_tab(char **tab);

// Event handling functions
int				handle_keypress(int keycode, t_game *game);
int				handle_keyrelease(int keycode, t_game *game);
int				handle_window_close(t_game *game);
int				handle_events(t_game *game);

int				parse_game_data(t_game *game, int argc, char **argv);
void			set_initial_direction(t_game *game);
int				close_window(t_game *game);
int				game_loop(t_game *game);

int				is_map_line(char *line);

int				process_pre_map_line(t_game *game, char *line, int *map_started,
					char **map_buffer, size_t *max_width);
int				process_map_line(char *line, char **map_buffer,
					size_t *max_width);
int				finalize_map(t_game *game, char *map_buffer);

int				is_texture_identifier(char *line);
int				parse_texture(t_game *game, char *line);
int				is_color_identifier(char *line);
int				parse_color_line(t_game *game, char *line);

int				check_floor_ceiling_texture(char *trimmed);

void			calculate_wall_height(t_game *g, t_ray_vars *vars);
void			calculate_texture_coords(t_game *g, t_ray_vars *vars);
void			draw_wall_stripe(t_game *g, t_ray_vars *vars, int x);

void			cast_ray(t_game *g, int x);
void			exit_with_error(t_game *g, const char *message);

void			update_movements(t_game *game);
void			render_3d(t_game *game);

#endif
