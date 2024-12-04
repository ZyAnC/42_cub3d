/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:49:35 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/25 18:15:56 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*tmpf(int fd, char *tmp)
{
	size_t	len;

	if (tmp)
		free(tmp);
	tmp = get_next_line(fd, 1);
	if (!tmp)
		return (NULL);
	len = ft_strlen(tmp);
	if (len > 0 && tmp[len - 1] == '\n')
		tmp[len - 1] = '\0';
	return (tmp);
}

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

char	**init_array(int rows, int cols)
{
	char	**map;
	int		i;
	int		j;

	map = malloc((rows + 1) * sizeof(char *));
	if (!map)
		error_message(5);
	i = 0;
	while (i < rows)
	{
		map[i] = malloc((cols + 2) * sizeof(char));
		if (!map[i])
		{
			j = 0;
			while (j <= i)
				free(map[j++]);
			free(map);
			error_message(5);
		}
		ft_memset(map[i], 'a', cols + 1);
		map[i][cols + 1] = '\0';
		i++;
	}
	map[i] = NULL;
	return (map);
}
int	valid_map_value(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'S' || c == 'W'
		|| c == ' ' || (c >= '\t' && c <= '\r'));
}
int	init_map_utils(t_imap *im)
{
	while (1)
	{
		im->tmp = tmpf(im->fd, im->tmp);
		if (!im->tmp)
			break ;
		im->j = -1;
		while (im->tmp[++im->j])
		{
			if (!valid_map_value(im->tmp[im->j]))
				return (0);
			if (im->tmp[im->j] != 32 && (im->tmp[im->j] < 9
					|| im->tmp[im->j] > 13))
				im->map[im->i][im->j] = im->tmp[im->j];
		}
		im->i++;
	}
	return (1);
}
int	reach_map_start(t_imap *im, char *filename, int rows)
{
	im->tmp = get_next_line(im->fd, 0);
	free(im->tmp);
	close(im->fd);
	im->i = im->height - rows + 1;
	im->tmp = NULL;
	im->fd = open(filename, O_RDONLY);
	if (im->fd == -1)
		return (0);
	while (im->i)
	{
		im->tmp = tmpf(im->fd, im->tmp);
		im->i--;
	}
	if (!init_map_utils(im))
		return (0);
	free(im->tmp);
	return (1);
}
char	**init_map(int rows, int cols, char *filename)
{
	t_imap	im;

	im.map = init_array(rows, cols);
	im.tmp = NULL;
	im.fd = open(filename, O_RDONLY);
	if (im.fd == -1)
		return (ft_freemap(&im, rows));
	im.height = 0;
	im.tmp = tmpf(im.fd, im.tmp);
	while (im.tmp != NULL)
	{
		im.tmp = tmpf(im.fd, im.tmp);
		if (!im.tmp)
			break ;
		im.height++;
	}
	free(im.tmp);
	if (!reach_map_start(&im, filename, rows))
		return (ft_freemap(&im, rows));
	im.tmp = get_next_line(im.fd, 0);
	free(im.tmp);
	close(im.fd);
	return (im.map);
}
