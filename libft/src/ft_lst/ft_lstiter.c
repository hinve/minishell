/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:31:36 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:20:18 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
		i++;
	}
}
/*
void print_element(void *content)
{
    int *element = (int*)content;
    printf("%d\n", *element);
}

int main()
{
    int *data1 = malloc(sizeof(int));
    int *data2 = malloc(sizeof(int));
    int *data3 = malloc(sizeof(int));
    *data1 = 42;
    *data2 = 99;
    *data3 = 123;
    t_list *node1 = ft_lstnew(data1);
    t_list *node2 = ft_lstnew(data2);
    t_list *node3 = ft_lstnew(data3);

    if (node1 != NULL && node2 != NULL && node3 != NULL) {
        node1->next = node2;
        node2->next = node3;
        ft_lstiter(node1, print_element);
    } else {
        printf("Memory allocation failed for one or more nodes.\n");
    }
    return 0;
} */