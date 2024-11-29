/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:37:50 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/29 20:08:00 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}
double	nor_angle(double angle)
{
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	while (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}
int get_color(int r, int g, int b)
{
	 int a = 0xFF;
 return (r << 24 | g << 16 | b << 8 | a );
}
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)	// put the pixel
{

	if (x < 0) // check the x position
		return ;
	else if (x >= S_W)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= S_H)
		return ;
	mlx_put_pixel(mlx->img, x, y, color); // put the pixel
}
 mlx_texture_t	*get_wallpng(t_mlx *mlx, int flag)
{
	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl); // normalize the angle
	if (flag == 0)
	{
		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
			return (mlx->tex->ea); // west wall
		else
			return (mlx->tex->we); // east wall
	}
	else
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return (mlx->tex->so); // south wall
		else
			return (mlx->tex->no); // north wall
	}
}
void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;

	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(mlx, ray, i++, get_color(mlx->floor->r,mlx->floor->g,mlx->floor->b)); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, get_color(mlx->cell->r,mlx->cell->g,mlx->cell->b)); // ceiling
}
double	get_x_o(mlx_texture_t	*texture, t_mlx *mlx)
{
	double	x_o;

	if (mlx->ray->flag == 1)
		x_o = (int)fmodf((mlx->ray->horiz_x * \
		(texture->width / TILE_SIZE)), texture->width);
	else
		x_o = (int)fmodf((mlx->ray->vert_y * \
		(texture->width / TILE_SIZE)), texture->width);
	return (x_o);
}
void	draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_wallpng(mlx, mlx->ray->flag);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, mlx);
	y_o = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(mlx, mlx->ray->index, t_pix, reverse_bytes \
		(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle));
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) /tan(mlx->ply->fov_rd / 2));
	b_pix = (S_H / 2) + (wall_h / 2);
	t_pix = (S_H / 2) - (wall_h / 2);
	if (b_pix > S_H)
		b_pix = S_H;
	if (t_pix < 0)
		t_pix = 0;
	mlx->ray->index = ray;
	draw_wall(mlx, t_pix, b_pix, wall_h);
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
}
int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}
int	wall_hit(float x, float y, t_mlx *mlx)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if ((y_m >= mlx->dt->h_map || x_m >= mlx->dt->w_map))
		return (0);
	if (mlx->dt->map2d[y_m] && x_m <= (int)ft_strlen(mlx->dt->map2d[y_m]))
		if (mlx->dt->map2d[y_m][x_m] == '1')
			return (0);
	return (1);
}
float	get_h_inter(t_mlx *mlx, float angl)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(mlx->ply->plyr_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = mlx->ply->plyr_x + (h_y - mlx->ply->plyr_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || \
		(!unit_circle(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx))
	{
		h_x += x_step;
		h_y += y_step;
	}
	mlx->ray->horiz_x = h_x;
	mlx->ray->horiz_y = h_y;
	return (sqrt(pow(h_x - mlx->ply->plyr_x, 2) + \
	pow(h_y - mlx->ply->plyr_y, 2)));
}

float	get_v_inter(t_mlx *mlx, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(mlx->ply->plyr_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = mlx->ply->plyr_y + (v_x - mlx->ply->plyr_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || \
	(!unit_circle(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, mlx))
	{
		v_x += x_step;
		v_y += y_step;
	}
	mlx->ray->vert_x = v_x;
	mlx->ray->vert_y = v_y;
	return (sqrt(pow(v_x - mlx->ply->plyr_x, 2) + \
	pow(v_y - mlx->ply->plyr_y, 2)));
}
void	cast_rays(t_mlx *mlx)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	mlx->ray->ray_ngl = mlx->ply->angle - (mlx->ply->fov_rd / 2);
	while (ray < S_W)
	{
		mlx->ray->flag = 0;
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_ngl));
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_ngl));
		if (v_inter <= h_inter)
			mlx->ray->distance = v_inter;
		else
		{
			mlx->ray->distance = h_inter;
			mlx->ray->flag = 1;
		}
		render_wall(mlx, ray);
		ray++;
		mlx->ray->ray_ngl += (mlx->ply->fov_rd / S_W);
	}
}

void	game_loop(void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	mlx_delete_image(mlx->mlx_c,mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_c, S_W, S_H);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_c, mlx->img, 0, 0);


}
void	init_player(t_mlx mlx)
{
	mlx.ply->plyr_x = mlx.dt->player->x * TILE_SIZE + TILE_SIZE / 2;
	mlx.ply->plyr_y = mlx.dt->player->y * TILE_SIZE + TILE_SIZE / 2;
	mlx.ply->fov_rd = FOV * M_PI / 180;
	if(mlx.dt->player->face == 'E')
		mlx.ply->angle = 0 ;
	else if(mlx.dt->player->face == 'S')
		mlx.ply->angle = M_PI /2;
	else if(mlx.dt->player->face == 'W')
		mlx.ply->angle = M_PI;
	else if(mlx.dt->player->face == 'N')
		mlx.ply->angle = 3 * M_PI / 2;
}
int	check_img(t_game *game)
{
	if(!mlx_load_png(game->npath))
		return (0);
	if(!mlx_load_png(game->wpath))
		return (0);
	if(!mlx_load_png(game->spath))
		return (0);
	if(!mlx_load_png(game->epath))
		return (0);
	return (1);
}
void	init_mlx(t_game *game)
{
	t_mlx	mlx;

	mlx.tex = (t_tex *)ft_calloc(sizeof(t_tex), 1);
	if(!check_img(game))
	{
		free(mlx.tex);
		free_all(game);
	}
	mlx.tex->no = mlx_load_png(game->npath);
	mlx.tex->we = mlx_load_png(game->wpath);
	mlx.tex->so = mlx_load_png(game->spath);
	mlx.tex->ea = mlx_load_png(game->epath);

	mlx.dt = calloc(1, sizeof(t_data));
	mlx.dt->map2d = game->map;
	mlx.dt->h_map = game->rows;
	mlx.dt->w_map = game->cols;
	mlx.dt->player = game->player;
	mlx.cell = game->cell;
	mlx.floor = game->floor;
	mlx.ply = ft_calloc(1, sizeof(t_player));
	mlx.ray = ft_calloc(1, sizeof(t_ray));
	mlx.mlx_c = mlx_init(S_W, S_H, "Cub3D", 0);
	init_player(mlx);
	mlx_loop_hook(mlx.mlx_c, &game_loop, &mlx);
		//game_loop(&mlx);
	mlx_loop(mlx.mlx_c);
}