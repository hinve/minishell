/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:47:07 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:19:40 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
/*
int main()
{
    int data1 = 42;
	int data2 = 99;
	int data3 = 123;
    t_list *node1 = ft_lstnew(&data1);
    t_list *node2 = ft_lstnew(&data2);
    t_list *node3 = ft_lstnew(&data3);
    if (node1 != NULL && node2 != NULL && node3 != NULL)
	{
        t_list *list = NULL;
        ft_lstadd_back(&list, node1);
        ft_lstadd_back(&list, node2);
        ft_lstadd_back(&list, node3);
        t_list *current = list;
        while (current != NULL) {
            int *content_ptr = (int *)current->content;
            printf("Content: %d\n", *content_ptr);
            current = current->next;
        }
        free(list);
    } else {
        printf("Memory allocation failed for one or more nodes.\n");
    }
    return 0;
} */
