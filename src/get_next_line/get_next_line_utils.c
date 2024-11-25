/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:20:34 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/25 12:57:09 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_getline(char *src)
{
	int		i;
	char	*line;

	i = 0;
	if (!src[i])
		return (NULL);
	while (src[i] && src[i] != '\n')
		i++;
	line = (char *)malloc((i + 1 + (src[i] == '\n')));
	if (!line)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		line[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		line[i] = src[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

size_t	fft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*fft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[fft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*fft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	str = (char *)malloc(((fft_strlen(s1)) + (fft_strlen(s2)) + 1));
	if (!str)
		return (ft_free(&s1));
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[fft_strlen(s1) + fft_strlen(s2)] = '\0';
	ft_free(&s1);
	return (str);
}

char	*getnewline(char *str)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (ft_free(&str));
	newstr = (char *)malloc((fft_strlen(str) - i + 1));
	if (!newstr)
		return (ft_free(&str));
	i++;
	j = 0;
	while (str[i])
		newstr[j++] = str[i++];
	newstr[j] = '\0';
	ft_free(&str);
	return (newstr);
}
