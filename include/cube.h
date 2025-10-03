// ===================================================================
// FILE: include/cube.h
// ===================================================================

#ifndef CUBE_H
# define CUBE_H

# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "minilibx-linux/mlx.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ MACROS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Math constants
# define M_PI 3.14159265358979323846

// Window dimensions
# define WIDTH 800
# define HEIGHT 600

// Map/player constants
# define BLOCK 64       // Size of a map block in pixels
# define FOV_DEG 60.0f
# define FOV_RAD (FOV_DEG * (M_PI / 180.0f))
# define MOVE_SPEED 0.2f
# define ROT_SPEED 0.005f
# define PLAYER_RADIUS 8.0f // Collision radius

// Raycasting constants
# define RAY_MAX 2000     // Max distance for simple raycasting
# define RAY_STEP 1.0f    // Step size for simple raycasting
# define NUM_RAYS WIDTH

// Minimap constants
# define MINIMAP_PADDING 10
# define MINIMAP_TILE 8
# define MINIMAP_RAYS 12

// Keycodes for Linux (X11)
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

// For get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ STRUCTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct s_dda
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	int		*side;   // Pointer to the original out_side
	float	*wall_x; // Pointer to the original wall_x
}	t_dda;

// Texture data struct
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_ray
{
	float	angle;
	float	dist;
	int		side;
	float	wall_x; // Where on the wall the ray hit (0.0 to 1.0)
}	t_ray;

typedef struct s_wall_slice
{
	int	height;
	int	y_start;
	int	y_end;
}	t_wall_slice;

typedef struct s_tex_info
{
	t_texture	*texture;
	int			tex_x;
	float		tex_pos;
}	t_tex_info;

// Player data
typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

// Texture and color configuration
typedef struct s_config
{
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		map_w;
	int		map_h;
	bool	checklist[6]; // NO, SO, WE, EA, F, C
}	t_config;

// Main game struct
typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	t_config	config;
	t_texture	textures[4]; // 0:N, 1:S, 2:W, 3:E
}	t_game;

// Linked list for map parsing
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;



// ~~~~~~~~~~~~~~~~~~~~~~ FUNCTION PROTOTYPES ~~~~~~~~~~~~~~~~~~~~~~~

// --- src/core ---
void			init_game(t_game *game);
void			init_config(t_config *config);
void			init_player(t_player *p, int start_tx, int start_ty, char direction);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				close_window(t_game *game);
void			exit_error(t_game *game, char *message);
void			free_game(t_game *game);
void			free_config(t_config *config);
int				draw_loop(void *param);

// --- src/parsing ---
void			parse_file(char *filename, t_game *game);
int				parse_color(char *line, t_game *game, char type_id);
int				parse_texture(char *line, t_game *game, char *type_id);
void			parse_map(t_list *map_list, t_game *game);
void			validate_map(t_game *game);
void			process_line(char *line, t_game *game,
						t_list **map_list, bool *is_parsing_map);

// --- src/player ---
void			move_player(t_game *game);
bool			touch_point(float px, float py, t_game *game, float radius);

// --- src/render ---
void			draw_minimap(t_game *g);
void			draw_3d_walls(t_game *g);
void			put_pixel(t_game *game, int x, int y, int color);
float			cast_ray_dda(t_game *g, float angle, int *out_side, float *wall_x);
unsigned int	get_pixel_color(t_texture *tex, int x, int y);
t_texture		*get_wall_texture(t_game *g, int side, float angle);
t_ray			calculate_ray_properties(t_game *g, int x);
t_wall_slice	calculate_slice_dimensions(t_ray *ray);
t_tex_info		prepare_texture_info(t_game *g, t_ray *ray);

// --- src/utils ---
char			*get_next_line(int fd);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
char			*ft_strtrim(char const *s1, char const *set);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
char			*ft_strchr(const char *s, int c);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **lst, t_list *new_node);
void			ft_lstclear(t_list **lst, void (*del)(void *));
int				ft_isspace(char c);
void			*ft_memset(void *s, int c, size_t n);
int				ft_lstsize(t_list *lst);
void			free_str_array(char **arr);

#endif
