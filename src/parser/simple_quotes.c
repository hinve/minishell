/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:03:23 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/14 10:26:09 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strncat(char *dest, const char *src, size_t n)
{
	char *d = dest;
	while (*d)
		d++;
	while (n-- && (*d++ = *src++))
		;
	if (n == (size_t)-1)
		*d = '\0';
	return dest;
}

char *ft_strstr(const char *haystack, const char *needle)
{
	if (!*needle)
		return (char *)haystack;

	for (; *haystack; haystack++)
	{
		const char *h = haystack;
		const char *n = needle;

		while (*h && *n && *h == *n)
		{
			h++;
			n++;
		}

		if (!*n)
			return (char *)haystack;
	}

	return NULL;
}
void remove_quotes_and_spaces(char **cmd)
{
	char *equal_pos;

	equal_pos = ft_strstr(*cmd, "=");
	if (equal_pos)
	{
		if (*(equal_pos + 1) == '\'')
		{
			char *closing_quote = ft_strchr(equal_pos + 2, '\'');
			if (closing_quote)
			{
				size_t prefix_len = equal_pos - *cmd + 1;
				size_t content_len = closing_quote - (equal_pos + 2);
				size_t suffix_len = ft_strlen(closing_quote + 1);
				char *new_cmd = malloc(prefix_len + content_len + suffix_len + 1);
				if (!new_cmd)
				{
					printf("Error: memoria insuficiente\n");
					exit(1);
				}
				strncpy(new_cmd, *cmd, prefix_len);
				new_cmd[prefix_len] = '\0';
				ft_strncat(new_cmd, equal_pos + 2, content_len);
				ft_strcat(new_cmd, closing_quote + 1);
				free(*cmd);
				*cmd = new_cmd;
			}
		}
	}
}