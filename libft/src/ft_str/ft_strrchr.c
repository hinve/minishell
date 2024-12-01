/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:09:50 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:22:44 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	while (i >= 0)
	{
		if (str[i] == (char) c)
		{
			return ((char *)&str[i]);
		}
		i--;
	}
	return (NULL);
}
/*
int main()
{
    char str[] = "Hello, World!";
    char *result;
	
    result = ft_strrchr(str, 'o');
    if (result != NULL) {
        printf("Found 'o' at position: %ld\n", result - str);
    } else {
        printf("Character 'o' not found.\n");
    }
    return 0;
} */