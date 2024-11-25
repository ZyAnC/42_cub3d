/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:34:20 by yzheng            #+#    #+#             */
/*   Updated: 2024/04/15 23:10:15 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int main() {
    char c = '5';  // 一个数字字符
    if (ft_isdigit(c)) {
        printf("'%c' is a digit.\n", c);
    } else {
        printf("'%c' is not a digit.\n", c);
    }
    return 0;
}*/
