/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:29:19 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/25 19:05:20 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int	check_rgb(const char *str)
{
	int		comma;
	int		i;

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
	token = ft_split(str,',');
	while(token[i])
	{
		num = ft_atoi(token[i]);
		if(ft_strlen(token[i++]) > 3 || num < 0 || num > 255)
		{
			free(str);
			pp_free(token);
			return(0);
		}
	}
	rgb->r = ft_atoi(token[0]);
	rgb->g = ft_atoi(token[1]);
	rgb->b = ft_atoi(token[2]);
	free(str);
	pp_free(token);
	return (1);
}
void	check_game(int fd,t_game *game,char *tmp)
{
	size_t	rows;
	size_t	cols;

	rows = 0;
	cols =ft_strlen(tmp);
	while(tmp != NULL)
	{

		tmp = tmpf(fd,tmp);
		if(!tmp)
			break ;
		rows++;
		if (ft_strlen(tmp) > cols)
			cols = ft_strlen(tmp);
		printf("%s\n",tmp);
	}
	printf("%zu\n",cols);
	printf("%zu\n",rows);
	(void)game;
}
