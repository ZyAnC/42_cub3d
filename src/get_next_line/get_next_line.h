/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:20:46 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/25 13:00:09 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

char	*get_next_line(int fd,int	i);
char	*getnewline(char *storage);
char	*fft_strjoin(char *s1, char *s2);
char	*fft_strchr( char *s, int c);
char	*ft_getline(char *src);
size_t	fft_strlen(const char *str);
char	*ft_free(char **str);

#endif
