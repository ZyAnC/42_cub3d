/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:18:51 by yzheng            #+#    #+#             */
/*   Updated: 2024/04/19 15:18:52 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*
#include <stdio.h>
int main()
{
    int a = 10;
    t_list *node = ft_lstnew(&a);
	// Create a new list node with content pointing to 'a'

    if (node != NULL) {
        printf("Node created. Node content: %d\n", *(int *)(node->content));
    } else {
        printf("Failed to create node.\n");
    }
    // Remember to free the allocated node after use
    free(node);

    return 0;
}*/
