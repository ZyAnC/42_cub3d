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
		return(NULL);
	len = ft_strlen(tmp);
	if (len > 0 && tmp[len - 1] == '\n')
		tmp[len - 1] = '\0';
	return (tmp);
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

void	get_texture(int fd, t_game *game)
{
	char	*tmp;

	tmp = NULL;
	tmp = tmpf(fd, tmp);
	if (ft_strncmp(tmp, "NO ./", 5))
		error_configuration(game, tmp, fd);
	game->npath = ft_strdup(tmp + 3);
	tmp = tmpf(fd, tmp);
	if (ft_strncmp(tmp, "SO ./", 5))
		error_configuration(game, tmp, fd);
	game->spath = ft_strdup(tmp + 3);
	tmp = tmpf(fd, tmp);
	if (ft_strncmp(tmp, "WE ./", 5))
		error_configuration(game, tmp, fd);
	game->wpath = ft_strdup(tmp + 3);
	tmp = tmpf(fd, tmp);
	if (ft_strncmp(tmp, "EA ./", 5))
		error_configuration(game, tmp, fd);
	game->epath = ft_strdup(tmp + 3);
	free(tmp);
}

void	get_rgb(int fd, t_game *game)
{
	char	*tmp;
	char	*rgb;


	tmp = NULL;
	tmp = tmpf(fd, tmp);
	if(tmp[0] != '\0')
		error_configuration(game, tmp, fd);
	tmp = tmpf(fd, tmp);
	rgb = ft_strdup(tmp + 2);
	if (ft_strncmp(tmp, "F ", 2) || !check_rgb(tmp) || !check_rgbrange(rgb,game->floor))
		error_configuration(game, tmp, fd);
	tmp = tmpf(fd, tmp);
	rgb = ft_strdup(tmp + 2);
	if (ft_strncmp(tmp, "C ", 2) || !check_rgb(tmp) || !check_rgbrange(rgb,game->cell))
		error_configuration(game, tmp, fd);
	free(tmp);
}


void	init_game(char *filename, t_game *game)
{
	int		fd;
	char	*tmp;

	tmp = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(game);
		error_message(4);
	}
	get_texture(fd, game);
	get_rgb(fd, game);
	tmp = tmpf(fd,tmp);

	if(tmp[0] != '\0')
		error_configuration(game, tmp, fd);
	check_game(fd,game,tmp);
}
