/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:33:13 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:22:20 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_length;

	src_length = 0;
	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			++i;
		}
		dest[i] = '\0';
	}
	while (src[src_length] != '\0')
	{
		++src_length;
	}
	return (src_length);
}
/*
int main()
{
	char dest[50] = "Hola";
	const char *src = "salut les potes";

	ft_strlcpy(dest, src, 10);
	printf("%s", dest);
	return (0);
}*/
