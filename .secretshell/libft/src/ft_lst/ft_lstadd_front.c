/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:01:09 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:19:45 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
int main()
{
    int data = 42;
    t_list *node = ft_lstnew(&data);

    if (node != NULL)
	{
        int newData = 99;
        t_list *newNode = ft_lstnew(&newData);
        if (newNode != NULL)
		{
            ft_lstadd_front(&node, newNode);
            t_list *current = node;
            while (current != NULL)
			{
                int *content_ptr = (int *)current->content;
                printf("Content: %d\n", *content_ptr);
                current = current->next;
            }
        	   free(node);
        }
		else
		{
            printf("Memory allocation failed for the new node.\n");
        }
    }
	else
	{
        printf("Memory allocation failed for the first node.\n");
    }
    return 0;
} */