/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:19:40 by yzheng            #+#    #+#             */
/*   Updated: 2025/04/03 21:48:44 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./MLX42/include/MLX42/MLX42.h"
# include "./src/get_next_line/get_next_line.h"
# include "./src/libft/libft.h"
# include "./src/printf/printf.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define S_W 1900
# define S_H 1000
# define TILE_SIZE 20
# define FOV 60
# define ROTATION_SPEED 0.035
# define PLAYER_SPEED 2
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_player
{
	int				plyr_x;
	int				plyr_y;
	double			angle;
	float			fov_rd;
	int				rot;
	int				l_r;
	int				u_d;
}					t_player;

typedef struct s_ray
{
	int				index;
	double			ray_ngl;
	double			horiz_x;
	double			horiz_y;
	double			vert_x;
	double			vert_y;
	double			distance;
	int				flag;
}					t_ray;
typedef struct s_tex
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}					t_tex;

typedef struct s_point
{
	char			face;
	int				count;
	int				x;
	int				y;
}					t_point;
typedef struct s_data
{
	char			**map2d;
	t_point			*player;
	int				w_map;
	int				h_map;
}					t_data;
typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;

}					t_rgb;

typedef struct s_mlx
{
	t_tex			*tex;
	mlx_image_t		*img;
	mlx_t			*mlx_c;
	t_ray			*ray;
	t_data			*dt;
	t_player		*ply;
	t_rgb			*floor;
	t_rgb			*cell;

}					t_mlx;

typedef struct s_game
{
	char			**map;
	char			*npath;
	char			*spath;
	char			*wpath;
	char			*epath;
	int				configs;
	t_point			*player;
	size_t			rows;
	size_t			cols;
	t_rgb			*floor;
	t_rgb			*cell;

}					t_game;
typedef struct initmap
{
	char			**map;
	int				i;
	int				j;
	int				height;
	int				fd;
	char			*tmp;
}					t_imap;
void				free_all(t_game *game);
void				init_game(char *filename, t_game *game);
void				error_message(int i);
void				error_configuration(t_game *game, char *tmp, int fd);
void				pp_free(char **fly);
char				*tmpf(int fd, char *tmp);
char				*get_texture(int fd, t_game *game);
int					check_rgb(const char *str);
int					check_rgbrange(char *str, t_rgb *rgb);
void				check_game(int fd, t_game *game, char *tmp, char *filename);
char				**init_array(int rows, int cols);
char				**init_map(int rows, int cols, char *filename);
void				init_mlx(t_game *game);
int					valid_map_value(char c);
char				*get_texture(int fd, t_game *game);
char				**ft_freemap(t_imap *im, int rows);
int					check_invalidzero(char c, t_game *game, int i, int j);
double				nor_angle(double angle);
double				get_x_o(mlx_texture_t *texture, t_mlx *mlx);
int					inter_check(float angle, float *inter, float *step,
						int is_horizon);
float				get_v_inter(t_mlx *mlx, float angl);
int					unit_circle(float angle, char c);
int					wall_hit(float x, float y, t_mlx *mlx);
void				draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix,
						int b_pix);
void				draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h);
void				render_wall(t_mlx *mlx, int ray);
int					wall_hit(float x, float y, t_mlx *mlx);
float				get_h_inter(t_mlx *mlx, float angl);
int					reverse_bytes(int c);
void				my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
mlx_texture_t		*get_wallpng(t_mlx *mlx, int flag);
int					check_img(t_game *game);
int					get_color(int r, int g, int b);
void				ft_exit(t_mlx *mlx);
void				move_player(t_mlx *mlx, double move_x, double move_y);
void				rotate_player(t_mlx *mlx, int i);
void				hook(t_mlx *mlx, double move_x, double move_y);
void				init_player(t_mlx mlx);
void				ft_reles(mlx_key_data_t keydata, t_mlx *mlx);
#endif
