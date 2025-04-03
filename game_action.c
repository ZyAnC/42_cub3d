/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:43:24 by yzheng            #+#    #+#             */
/*   Updated: 2025/04/03 21:47:55 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	int	map_grid_y;
	int	map_grid_x;
	int	new_x;
	int	new_y;
	int	buffer;

	buffer = 5;
	new_x = roundf(mlx->ply->plyr_x + move_x);
	new_y = roundf(mlx->ply->plyr_y + move_y);
	map_grid_x = (new_x / TILE_SIZE);
	map_grid_y = (new_y / TILE_SIZE);
	if (mlx->dt->map2d[map_grid_y][map_grid_x] != '1')
	{
		if (mlx->dt->map2d[map_grid_y][(int)(new_x + buffer) / TILE_SIZE] != '1'
			&& mlx->dt->map2d[map_grid_y][(int)(new_x - buffer)
			/ TILE_SIZE] != '1' && mlx->dt->map2d[(int)(new_y + buffer)
			/ TILE_SIZE][map_grid_x] != '1' && mlx->dt->map2d[(int)(new_y
				- buffer) / TILE_SIZE][map_grid_x] != '1')
		{
			mlx->ply->plyr_x = new_x;
			mlx->ply->plyr_y = new_y;
		}
	}
}

void	rotate_player(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->ply->angle += ROTATION_SPEED;
		if (mlx->ply->angle > 2 * M_PI)
			mlx->ply->angle -= 2 * M_PI;
	}
	else
	{
		mlx->ply->angle -= ROTATION_SPEED;
		if (mlx->ply->angle < 0)
			mlx->ply->angle += 2 * M_PI;
	}
}

void	hook(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->ply->l_r == 1)
	{
		move_x = -sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = cos(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->l_r == -1)
	{
		move_x = sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->u_d == 1)
	{
		move_x = cos(mlx->ply->angle) * PLAYER_SPEED;
		move_y = sin(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->u_d == -1)
	{
		move_x = -cos(mlx->ply->angle) * PLAYER_SPEED;
		move_y = -sin(mlx->ply->angle) * PLAYER_SPEED;
	}
	move_player(mlx, move_x, move_y);
}

void	init_player(t_mlx mlx)
{
	mlx.ply->plyr_x = mlx.dt->player->x * TILE_SIZE + TILE_SIZE / 2;
	mlx.ply->plyr_y = mlx.dt->player->y * TILE_SIZE + TILE_SIZE / 2;
	mlx.ply->fov_rd = FOV * M_PI / 180;
	if (mlx.dt->player->face == 'E')
		mlx.ply->angle = 0;
	else if (mlx.dt->player->face == 'S')
		mlx.ply->angle = M_PI / 2;
	else if (mlx.dt->player->face == 'W')
		mlx.ply->angle = M_PI;
	else if (mlx.dt->player->face == 'N')
		mlx.ply->angle = 3 * M_PI / 2;
}

void	ft_reles(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		mlx->ply->l_r = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		mlx->ply->l_r = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		mlx->ply->u_d = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		mlx->ply->u_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		mlx->ply->rot = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		mlx->ply->rot = 0;
}
