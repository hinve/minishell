/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:56:29 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:20:53 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = s;
	while (n-- > 0)
	{
		if (*p == (unsigned char)c)
		{
			return ((void *)p);
		}
		p++;
	}
	return (NULL);
}
/*
int main()
{
    char str[] = "Hello, World!";
    char *result;
    // Search for the first occurrence of 'W' in str
    result = (char *)ft_memchr(str, 'W', ft_strlen(str));
    if (result != NULL) {
        printf("Found 'W' at position: %ld\n", result - str);
    } else {
        printf("Character 'W' not found.\n");
    }
    return 0;
} */
