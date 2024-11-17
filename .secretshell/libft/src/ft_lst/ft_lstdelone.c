/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:02:56 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:19:54 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		del(lst->content);
		free(lst);
		lst = NULL;
	}
}
/*
static void	del(void *data)
{
	free(data);
}

int main()
{
	int *data = malloc(sizeof(int));
	if (data != NULL)
	{
		*data = 42;
		t_list *node = ft_lstnew(data);
		if (node != NULL)
		{
			ft_lstdelone(node, del);
			if (node != NULL)
			{
				printf("Node has been successfully deleted.\n");
			}
			else
			{
				printf("Node has not been deleted.\n");
			}
		} else {
			printf("Memory allocation failed for the node.\n");
		}
	} else {
		printf("Memory allocation failed for the data.\n");
	}
	return 0;
}*/