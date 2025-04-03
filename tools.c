/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:04:08 by yzheng            #+#    #+#             */
/*   Updated: 2025/04/03 21:48:50 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pp_free(char **fly)
{
	int	j;

	if (!fly || !*fly)
		return ;
	j = 0;
	while (fly[j])
		free(fly[j++]);
	free(fly);
	fly = NULL;
}

void	error_configuration(t_game *game, char *tmp, int fd)
{
	ft_printf("Error\nMisconfiguration!");
	free(tmp);
	tmp = get_next_line(fd, 0);
	free(tmp);
	if (game->npath)
		free(game->npath);
	if (game->spath)
		free(game->spath);
	if (game->wpath)
		free(game->wpath);
	if (game->epath)
		free(game->epath);
	free(game->floor);
	free(game->cell);
	free(game);
	close(fd);
	exit(1);
}

char	**ft_freemap(t_imap *im, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(im->map[i++]);
	free(im->map);
	im->map = NULL;
	free(im->tmp);
	im->tmp = get_next_line(im->fd, 0);
	free(im->tmp);
	close(im->fd);
	return (NULL);
}

int	check_invalidzero(char c, t_game *game, int i, int j)
{
	if (game->player->count > 1)
		return (1);
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
	{
		game->player->y = i;
		game->player->x = j;
		game->player->face = c;
	}
	return ((c == '0' || c == 'N' || c == 'W' || c == 'E' || c == 'S')
		&& (game->map[i - 1][j] == 'a' || game->map[i + 1][j] == 'a'
			|| game->map[i][j - 1] == 'a' || game->map[i][j + 1] == 'a'));
}

void	ft_exit(t_mlx *mlx)
{
	int	i;

	i = 0;
	mlx_delete_image(mlx->mlx_c, mlx->img);
	mlx_close_window(mlx->mlx_c);
	while (mlx->dt->map2d[i])
		free(mlx->dt->map2d[i++]);
	if (mlx->tex->no)
		mlx_delete_texture(mlx->tex->no);
	if (mlx->tex->so)
		mlx_delete_texture(mlx->tex->so);
	if (mlx->tex->we)
		mlx_delete_texture(mlx->tex->we);
	if (mlx->tex->ea)
		mlx_delete_texture(mlx->tex->ea);
	free(mlx->dt->map2d);
	free(mlx->dt->player);
	free(mlx->dt);
	free(mlx->ply);
	free(mlx->ray);
	free(mlx->tex);
	mlx_terminate(mlx->mlx_c);
	exit(0);
}
