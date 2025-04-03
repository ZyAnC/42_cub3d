/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:39:30 by yzheng            #+#    #+#             */
/*   Updated: 2025/04/03 21:47:18 by yzheng           ###   ########.fr       */
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

int	get_color(int r, int g, int b)
{
	int	a;

	a = 0xFF;
	return (r << 24 | g << 16 | b << 8 | a);
}

int	check_img(t_game *game)
{
	mlx_texture_t	*check;

	check = mlx_load_png(game->npath);
	if (!check)
		return (0);
	mlx_delete_texture(check);
	check = mlx_load_png(game->wpath);
	if (!check)
		return (0);
	mlx_delete_texture(check);
	check = mlx_load_png(game->spath);
	if (!check)
		return (0);
	mlx_delete_texture(check);
	check = mlx_load_png(game->epath);
	if (!check)
		return (0);
	mlx_delete_texture(check);
	return (1);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= S_W)
		return ;
	if (y < 0)
		return ;
	else if (y >= S_H)
		return ;
	mlx_put_pixel(mlx->img, x, y, color);
}

mlx_texture_t	*get_wallpng(t_mlx *mlx, int flag)
{
	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl);
	if (flag == 0)
	{
		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
			return (mlx->tex->ea);
		else
			return (mlx->tex->we);
	}
	else
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return (mlx->tex->so);
		else
			return (mlx->tex->no);
	}
}
