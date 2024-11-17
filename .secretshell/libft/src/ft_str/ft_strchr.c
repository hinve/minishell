/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:09:46 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:21:59 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if (str[i] == (unsigned char)c)
	{
		return (((char *)&str[i]));
	}
	return (NULL);
}
/*
int main()
{
    const char *str1 = "Hello, World!";
    const char *str2 = "GitHub Copilot";
    const char *str3 = "1234567890";

    printf("Searching for 'o' in \"%s\": %s\n", str1, ft_strchr(str1, 'o'));
    printf("Searching for 'C' in \"%s\": %s\n", str2, ft_strchr(str2, 'C'));
    printf("Searching for '0' in \"%s\": %s\n", str3, ft_strchr(str3, '0'));
    printf("Searching for 'z' in \"%s\": %s\n", str1, ft_strchr(str1, 'z'));

    return 0;
}*/