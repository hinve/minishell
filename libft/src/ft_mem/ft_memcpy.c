/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:09:36 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:21:02 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	char		*pdest;
	const char	*psrc;

	pdest = dest;
	psrc = src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (size-- > 0)
	{
		*pdest++ = *psrc++;
	}
	return (dest);
}
/*
int main()
{
    char source[] = "Hello, World!";
    char destination[20];

    ft_memcpy(destination, source, ft_strlen(source) + 1);
	
    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);
    return 0;
}*/
