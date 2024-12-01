/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:25:04 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:22:53 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	*str_new(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*str_ptr;

	if (!s)
		return (NULL);
	if (start > (unsigned int) ft_strlen(s))
		len = 0;
	else if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	str = str_new(len);
	if (!str)
		return (NULL);
	s += start;
	str_ptr = str;
	*(str + len) = '\0';
	while (len-- && *s)
		*str++ = *s++;
	return (str_ptr);
}
/*
int main()
{
    const char original[] = "Hello, World!"; 
    char *sub = ft_substr(original, 7, 5);
    if (sub != NULL) {
        printf("Original: %s\n", original);
        printf("Substring: %s\n", sub);
        free(sub);
    } else {
        printf("Invalid input or memory allocation failed.\n");
    }
    return 0;
} */