/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:04:08 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/26 11:56:17 by yzheng           ###   ########.fr       */
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
