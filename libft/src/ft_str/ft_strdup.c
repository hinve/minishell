/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:05:26 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:22:04 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *source)
{
	char	*dup;
	int		len;

	dup = (char *)malloc(ft_strlen(source) + 1);
	if (source == NULL)
	{
		return (NULL);
	}
	if (dup != NULL)
	{
		len = ft_strlen(source) + 1;
		ft_strlcpy(dup, source, len);
	}
	return (dup);
}
/*
int main()
{
    const char original[] = "Hello, World!";
    char *duplicate;

    duplicate = ft_strdup(original);
    if (duplicate != NULL)
	{
        printf("Original: %s\n", original);
        printf("Duplicate: %s\n", duplicate);

        free(duplicate);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
} */