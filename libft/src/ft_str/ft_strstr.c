/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matteo <matteo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 23:49:41 by matteo            #+#    #+#             */
/*   Updated: 2024/11/20 23:50:34 by matteo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char *ft_strstr(const char *haystack, const char *needle)
{
    const char *h;
    const char *n;

    if (!*needle)
        return (char *)haystack;

    while (*haystack)
    {
        h = haystack;
        n = needle;
        while (*h && *n && *h == *n)
        {
            h++;
            n++;
        }
        if (!*n)
            return (char *)haystack;
        haystack++;
    }
    return (NULL);
}