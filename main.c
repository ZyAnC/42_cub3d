/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:13:28 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/26 10:39:19 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_message(int i)
{
	if (!i)
		ft_printf("Miss mapfile");
	else if (i == 2)
		ft_printf("Too many arguments");
	else if (i == 3)
		ft_printf("Wrong map format");
	else if (i == 4)
		ft_printf("Failed to open file");
	else if (i == 5)
		ft_printf("Allocate failed");
	else if (i == 6)
		ft_printf("Read failed");
	else if (i == 7)
		ft_printf("Too huge map");
	exit(1);
}



void	checkgamename(char *filename)
{
	char	*result;
	t_game	*game;

	result = ft_strnstr(filename, ".cub", ft_strlen(filename));
	if (result != NULL)
	{
		if ((result + 3) == (filename + ft_strlen(filename) - 1))
		{
			game = malloc(sizeof(t_game));
			if (!game)
				error_message(5);
			game->npath = NULL;
			game->spath = NULL;
			game->wpath = NULL;
			game->epath = NULL;
			game->floor = (t_rgb *)malloc(sizeof(t_rgb));
			if (!game->floor)
				error_message(5);
			game->cell = (t_rgb *)malloc(sizeof(t_rgb));
			if (!game->cell)
				error_message(5);
			init_game(filename,game);
		}
	}
	else
		error_message(3);
}

int	main(int ac, char **av)
{
	if (ac == 1)
		error_message(0);
	else if (ac == 2)
		checkgamename(av[1]);
	else
		error_message(2);
}
