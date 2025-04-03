/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:26:42 by yzheng            #+#    #+#             */
/*   Updated: 2025/04/03 21:27:48 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_rgb(char *tmp)
{
	if (tmp && !ft_strlen(tmp))
		return (1);
	if (!ft_strncmp(tmp, "NO ./", 5))
		return (2);
	if (!ft_strncmp(tmp, "SO ./", 5))
		return (3);
	if (!ft_strncmp(tmp, "WE ./", 5))
		return (4);
	if (!ft_strncmp(tmp, "EA ./", 5))
		return (5);
	if (!ft_strncmp(tmp, "F ", 2))
		return (6);
	if (!ft_strncmp(tmp, "C ", 2))
		return (7);
	if (tmp && ft_strlen(tmp))
		return (8);
	return (0);
}

void	parse_rgb(int type, char *tmp, t_game *game, int fd)
{
	if (type == 6)
	{
		if (!check_rgb(tmp) || !check_rgbrange(ft_strdup(tmp + 2), game->floor))
			error_configuration(game, tmp, fd);
	}
	if (type == 7)
	{
		if (!check_rgb(tmp) || !check_rgbrange(ft_strdup(tmp + 2), game->cell))
			error_configuration(game, tmp, fd);
	}
}

int	set_config(t_game *game, char *tmp, int type, int fd)
{
	if (type == 3 || type == 4 || type == 5 || type == 2)
		if (!ft_strnstr(tmp, ".png", ft_strlen(tmp)))
			return (0);
	if (type == 1)
		return (type);
	if (type == 2)
		game->npath = ft_strdup(tmp + 3);
	else if (type == 3)
		game->spath = ft_strdup(tmp + 3);
	else if (type == 4)
		game->wpath = ft_strdup(tmp + 3);
	else if (type == 5)
		game->epath = ft_strdup(tmp + 3);
	else if (type == 6 || type == 7)
		parse_rgb(type, tmp, game, fd);
	if (type == 8 && game->configs != 6)
		return (0);
	else if (type == 8 && game->configs == 6)
		return (-1);
	if (type > 1)
		game->configs++;
	return (type);
}

char	*get_texture(int fd, t_game *game)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (1)
	{
		tmp = tmpf(fd, tmp);
		i = set_config(game, tmp, get_texture_rgb(tmp), fd);
		if (i == -1)
			break ;
		else if (i == 0)
			error_configuration(game, tmp, fd);
	}
	return (tmp);
}

int	valid_map_value(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'S' || c == 'W'
		|| c == ' ' || (c >= '\t' && c <= '\r'));
}
