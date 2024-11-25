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

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;

}	t_rgb;

typedef struct s_game
{
	char	*npath;
	char	*spath;
	char	*wpath;
	char	*epath;
	t_rgb	*floor;
	t_rgb	*cell;

}	t_game;

void	init_game(char *filename, t_game *game);
void	error_message(int i);
void	pp_free(char **fly);
char	*tmpf(int fd, char *tmp);
int	check_rgb(const char *str);
int	check_rgbrange(char *str, t_rgb *rgb);
void	check_game(int fd,t_game *game,char *tmp);
#endif
