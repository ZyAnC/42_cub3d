/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:37:50 by yzheng            #+#    #+#             */
/*   Updated: 2025/04/03 21:48:27 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (mlx->ply->rot == 1)
		rotate_player(mlx, 1);
	if (mlx->ply->rot == -1)
		rotate_player(mlx, 0);
	hook(mlx, 0, 0);
	cast_rays(mlx);
}

void	key_hook(mlx_key_data_t keydata, void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		ft_exit(mlx);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		mlx->ply->l_r = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		mlx->ply->l_r = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		mlx->ply->u_d = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		mlx->ply->u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		mlx->ply->rot = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		mlx->ply->rot = 1;
	ft_reles(keydata, mlx);
}

void	load_tex(t_mlx *mlx, t_game *game)
{
	mlx->tex = (t_tex *)ft_calloc(sizeof(t_tex), 1);
	if (!check_img(game))
	{
		free(mlx->tex);
		free_all(game);
	}
	mlx->tex->no = mlx_load_png(game->npath);
	mlx->tex->we = mlx_load_png(game->wpath);
	mlx->tex->so = mlx_load_png(game->spath);
	mlx->tex->ea = mlx_load_png(game->epath);
	if (game->npath)
		free(game->npath);
	if (game->spath)
		free(game->spath);
	if (game->wpath)
		free(game->wpath);
	if (game->epath)
		free(game->epath);
}

void	init_mlx(t_game *game)
{
	t_mlx	mlx;

	load_tex(&mlx, game);
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
	mlx.img = mlx_new_image(mlx.mlx_c, S_W, S_H);
	mlx_image_to_window(mlx.mlx_c, mlx.img, 0, 0);
	mlx_loop_hook(mlx.mlx_c, &game_loop, &mlx);
	mlx_key_hook(mlx.mlx_c, &key_hook, &mlx);
	mlx_loop(mlx.mlx_c);
	ft_exit(&mlx);
}
