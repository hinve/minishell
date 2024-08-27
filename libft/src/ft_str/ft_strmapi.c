/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:00:15 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:22:28 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	f(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	else
		return (c);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	result = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
int main()
{
	const char *original = "abcdef";
	char *mappedStr = ft_strmapi(original, f);
	if (mappedStr != NULL)
	{
		printf("Original: %s\n", original);
		printf("Mapped:   %s\n", mappedStr);
		// Free the memory allocated for the mapped string
		free(mappedStr);
	} else {
		printf("Memory allocation failed.\n");
	}
	return 0;
} */