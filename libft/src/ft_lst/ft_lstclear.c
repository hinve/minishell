/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:06:46 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:19:49 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = tmp;
		}
	}
}
/*
static void	del(void *data)
{
	free(data);
}

int main()
{
    int *data1 = malloc(sizeof(int));
    int *data2 = malloc(sizeof(int));
    int *data3 = malloc(sizeof(int));
    if (data1 != NULL && data2 != NULL && data3 != NULL)
    {
        *data1 = 42;
        *data2 = 99;
        *data3 = 123;
        t_list *node1 = ft_lstnew(data1);
        t_list *node2 = ft_lstnew(data2);
        t_list *node3 = ft_lstnew(data3);
        if (node1 != NULL && node2 != NULL && node3 != NULL)
        {
            node1->next = node2;
            node2->next = node3;
            ft_lstclear(&node1, del);
        } else {
            printf("Memory allocation failed for one or more nodes.\n");
        }
    } else {
        printf("Memory allocation failed for one or more data.\n");
    }
    return 0;
}*/