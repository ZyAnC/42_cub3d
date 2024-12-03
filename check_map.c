/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:29:19 by yzheng            #+#    #+#             */
/*   Updated: 2024/12/03 19:40:16 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_rgb(const char *str)
{
	int	comma;
	int	i;

	comma = 0;
	i = 2;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (0);
		if (str[i] == ',')
		{
			if (i == 0 || str[i - 1] == ',' || !ft_isdigit(str[i + 1]))
				return (0);
			comma++;
		}
		i++;
	}
	if (comma != 2)
		return (0);
	return (1);
}
int	check_rgbrange(char *str, t_rgb *rgb)
{
	char	**token;
	int		num;
	int		i;

	i = 0;
	token = ft_split(str, ',');
	free(str);
	while (token[i])
	{
		num = ft_atoi(token[i]);
		if (ft_strlen(token[i++]) > 3 || num < 0 || num > 255)
		{
			pp_free(token);
			return (0);
		}
	}
	rgb->r = ft_atoi(token[0]);
	rgb->g = ft_atoi(token[1]);
	rgb->b = ft_atoi(token[2]);
	pp_free(token);
	return (1);
}

void	free_all(t_game *game)
{
	size_t	i;

	i = 0;
	ft_printf("Error\nMisconfiguration!");
	free(game->player);
	while (i < game->rows)
		free(game->map[i++]);
	free(game->map);
	game->map = NULL;
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
	exit(1);
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
void	check_map(t_game *game)
{
	size_t	i;
	size_t	j;
	char	c;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			c = game->map[i][j];
			if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
				game->player->count++;
			if ((c == '0' || c == 'N' || c == 'W' || c == 'E' || c == 'S')
				&& (j == 0 || j == game->cols - 1))
				free_all(game);
			if ((c == '0' || c == 'N' || c == 'W' || c == 'E' || c == 'S')
				&& (i == 0 || i == game->rows - 1))
				free_all(game);
			if (check_invalidzero(c, game, i, j))
				free_all(game);
			j++;
		}
		i++;
	}
}

void	check_game(int fd, t_game *game, char *tmp, char *filename)
{
	game->rows = 1;
	game->cols = ft_strlen(tmp);
	while (tmp != NULL)
	{
		tmp = tmpf(fd, tmp);
		if (!tmp)
			break ;
		game->rows++;
		if (ft_strlen(tmp) > game->cols)
			game->cols = ft_strlen(tmp);
	}
	free(tmp);
	tmp = get_next_line(fd, 0);
	free(tmp);
	close(fd);
	game->map = init_map(game->rows, game->cols, filename);
	if (!game->map)
		free_all(game);
	check_map(game);
	if (game->player->count == 0)
		free_all(game);
	init_mlx(game);
	free_all(game);
}
