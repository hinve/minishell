/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:42:57 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:20:49 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t n_elements, size_t size)
{
	void	*ptr;

	ptr = malloc(n_elements * size);
	if (ptr != NULL)
	{
		ft_bzero(ptr, (n_elements * size));
	}
	return (ptr);
}
/*
int main()
{
    int *arr;
    size_t num_elements = 5;
	size_t i = 0;
	
    arr = (int *)calloc(num_elements, sizeof(int));
    if (arr != NULL)
	{
        while (i < num_elements)
		{
            printf("arr[%zu] = %d\n", i, arr[i]);
			i++;
        }
        free(arr);
    }
	else
	{
        printf("Memory allocation failed.\n");
    }
    return 0;
} */