/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:29:19 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/26 17:53:27 by yzheng           ###   ########.fr       */
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
}
