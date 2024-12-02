/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:44:17 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/02 12:26:29 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t	i;

    i = 0;
    while (i < n && (s1[i] || s2[i]))
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

    result = ft_strncmp(str1, str2, 6);
    if (result == 0) {
        printf("The first 6 characters are equal.\n");
    } else if (result < 0) {
        printf("The first 6 characters of str1 are less than str2.\n");
    } else {
        printf("The first 6 characters of str1 are greater than str2.\n");
    }
    return 0;
} */