/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:21:22 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:20:28 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*save;

	if (!lst || !f || !del)
		return (0);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (0);
	save = new_list;
	lst = lst->next;
	while (lst)
	{
		new_list->next = ft_lstnew(f(lst->content));
		if (!new_list->next)
		{
			ft_lstclear(&save, del);
			return (0);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	new_list->next = NULL;
	return (save);
}
/*
void print_element(void *content)
{
    int *element = (int*)content;
    printf("%d\n", *element);
}

void *double_int(void *content)
{
    int *element = (int*)content;
    int *new_element = malloc(sizeof(int));
    if (new_element)
    {
        *new_element = *element * 2;
    }
    return new_element;
}

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
        node1->next = node2;
        node2->next = node3;
        t_list *new_list = ft_lstmap(node1, double_int, free);
        ft_lstiter(new_list, print_element);
        ft_lstclear(&new_list, free);
    } else {
        printf("Memory allocation failed for one or more nodes.\n");
    }
    return 0;
}
*/