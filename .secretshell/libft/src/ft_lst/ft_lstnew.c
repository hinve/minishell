/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:59:10 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:20:33 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*
 int main()
 {
    // Create a new linked list node with an integer content
    int data = 42;
    t_list *node = ft_lstnew(&data);
    if (node != NULL) {
        // Access the content of the node
        int *content_ptr = (int *)node->content;
        printf("Content: %d\n", *content_ptr);
        // Free the memory allocated for the node
        free(node);
    } else {
        printf("Memory allocation failed for the node.\n");
    }
    return 0;
} */