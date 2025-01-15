/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:03:23 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/14 12:18:51 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*d;

	d = dest;
	while (*d)
		d++;
	while (n--)
	{
		*d = *src;
		d++;
		src++;
	}
	if (n == (size_t)-1)
		*d = '\0';
	return (dest);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;

	if (!*needle)
		return ((char *)haystack);
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
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

void	handle_memory_error(void)
{
	printf("Error: memoria insuficiente\n");
	exit(1);
}

char	*create_new_cmd(char *cmd, char *equal_pos, char *closing_quote)
{
	size_t	prefix_len;
	size_t	content_len;
	size_t	suffix_len;
	char	*new_cmd;

	prefix_len = equal_pos - cmd + 1;
	content_len = closing_quote - (equal_pos + 2);
	suffix_len = ft_strlen(closing_quote + 1);
	new_cmd = malloc(prefix_len + content_len + suffix_len + 1);
	if (!new_cmd)
		handle_memory_error();
	ft_strncpy(new_cmd, cmd, prefix_len);
	new_cmd[prefix_len] = '\0';
	ft_strncat(new_cmd, equal_pos + 2, content_len);
	ft_strcat(new_cmd, closing_quote + 1);
	return (new_cmd);
}

void	remove_quotes_and_spaces(char **cmd)
{
    char	*equal_pos;
    char	*closing_quote;
    char	*new_cmd;
    char	quote_char;

    equal_pos = ft_strstr(*cmd, "=");
    if (equal_pos && (*(equal_pos + 1) == '\'' || *(equal_pos + 1) == '\"'))
    {
        quote_char = *(equal_pos + 1);
        closing_quote = ft_strchr(equal_pos + 2, quote_char);
        if (closing_quote)
        {
            new_cmd = create_new_cmd(*cmd, equal_pos, closing_quote);
            free(*cmd);
            *cmd = new_cmd;
        }
    }
}
