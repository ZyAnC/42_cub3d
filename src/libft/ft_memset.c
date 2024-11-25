/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:54:38 by yzheng            #+#    #+#             */
/*   Updated: 2024/04/15 23:16:17 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;

	s = b;
	while (len--)
		*s++ = (unsigned char)c;
	return (b);
}
/*
#include <stdio.h>
#include <string.h>

void print_memory(const char *mem, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        printf("%d ", (unsigned char)mem[i]);
    }
    printf("\n");
}

int main() {
    char buffer[10];

	//ft_memset(((void *)0), 'a', 12);
	memset(((void *)0), 'a', 12);
   //ft_memset(buffer, 256, sizeof(buffer));
    print_memory(buffer, sizeof(buffer));

    return 0;
}*/
