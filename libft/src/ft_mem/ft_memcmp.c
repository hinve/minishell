/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:03:01 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:20:58 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ss1;
	const unsigned char	*ss2;
	size_t				i;

	i = 0;
	ss1 = (const unsigned char *)s1;
	ss2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}
/*
int main()
{
    char str1[] = "Hello, World!";
    char str2[] = "Hello, Universe!";
    int result;

    result = ft_memcmp(str1, str2, 10);
    if (result == 0) {
        printf("The first 10 characters are equal.\n");
    } else if (result < 0) {
        printf("The first 10 characters of str1 are less than str2.\n");
    } else {
        printf("The first 10 characters of str1 are greater than str2.\n");
    }
    return 0;
} */