/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:24:53 by yzheng            #+#    #+#             */
/*   Updated: 2025/04/03 21:30:23 by yzheng           ###   ########.fr       */
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
