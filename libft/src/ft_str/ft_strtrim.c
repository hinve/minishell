/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:33:58 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:22:49 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	str = malloc(end - start + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[start], end - start + 2);
	return (str);
}
/*
int main()
{
    const char *original = "   Hello, World!   ";
    const char *set = " \t";  // Whitespace characters
    char *trimmedStr = ft_strtrim(original, set);
	
    if (trimmedStr != NULL) {
        printf("Original: '%s'\n", original);
        printf("Trimmed:  '%s'\n", trimmedStr);
        // Free the memory allocated for the trimmed string
        free(trimmedStr);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
} */