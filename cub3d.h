#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "./MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include "./src/printf/printf.h"
# include "./src/libft/libft.h"
# include "./src/get_next_line/get_next_line.h"
#include <math.h>
# define S_W 1900 // screen width
# define S_H 1000 // screen height
# define TILE_SIZE 20 // tile size
# define FOV 60 // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 4	// player speed
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
typedef struct s_player //the player structure
{
	int		plyr_x; // player x position in pixels
	int		plyr_y; // player y position in pixels
	double	angle;	// player angle
	float	fov_rd;	// field of view in radians
	int		rot;	// rotation flag
	int		l_r;	// left right flag
	int		u_d;	// up down flag
}	t_player;

typedef struct s_ray
{
	int		index;
	double	ray_ngl;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	double	distance;
	int		flag;
}	t_ray;
typedef struct s_tex
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_tex;

typedef struct s_point
{
	char	face;
	int	count;
	int	x;
	int	y;
}	t_point;
typedef struct s_data	//the data structure
{
	char	**map2d;	// the map
	t_point *player;
	int		w_map;		// map width
	int		h_map;		// map height
}	t_data;
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;

}	t_rgb;

typedef struct s_mlx	//the mlx structure
{
	t_tex			*tex;
	mlx_image_t		*img;	// the image
	mlx_t			*mlx_c;	// the mlx pointer
	t_ray			*ray;	// the ray structure
	t_data			*dt;	// the data structure
	t_player		*ply;	// the player structure
	t_rgb	*floor;
	t_rgb	*cell;
}	t_mlx;



typedef struct s_game
{
	char	**map;
	char	*npath;
	char	*spath;
	char	*wpath;
	char	*epath;
	int		configs;
	t_tex			*tex;
	t_point *player;
	size_t		rows;
	size_t		cols;
	t_rgb	*floor;
	t_rgb	*cell;
	mlx_t			*mlx;
}	t_game;
typedef struct initmap
{
	char	**map;
	int		i;
	int		j;
	int		fd;
	char	*tmp;
}	t_imap;
void	free_all(t_game *game);
void	init_game(char *filename, t_game *game);
void	error_message(int i);
void	error_configuration(t_game *game, char *tmp, int fd);
void	pp_free(char **fly);
char	*tmpf(int fd, char *tmp);
int	check_rgb(const char *str);
int	check_rgbrange(char *str, t_rgb *rgb);
void	check_game(int fd,t_game *game,char *tmp,char *filename);
char	**init_array(int rows, int cols);
char	**init_map(int rows, int cols, char *filename);
 void init_mlx(t_game *game);
#endif
