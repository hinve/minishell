/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:05:26 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/02 18:41:30 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s) + 1;
	dup = malloc(len);
	if (dup)
		ft_strlcpy(dup, s, len);
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