/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:32:22 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/07 14:33:16 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *append_str(char *dest, const char *src)
{
    if (!src)
        return (dest);
    int dl = ft_strlen(dest);
    int sl = ft_strlen(src);
    char *new_str = (char *)malloc(dl + sl + 1);
    int i = 0;
    while (dest && dest[i])
    {
        new_str[i] = dest[i];
        i++;
    }
    for (int j = 0; j < sl; j++)
        new_str[i++] = src[j];
    new_str[i] = '\0';
    free(dest);
    return (new_str);
}

char *expand_heredoc(char *line, t_env *env)
{
    int i = 0;
    char *temp = ft_strdup("");
    while (line && line[i])
    {
        if (line[i] == '$')
            temp = append_str(temp, get_value(env, "VAR"));
        else if (line[i] == '~' && (!line[i + 1] || line[i + 1] == '/'))
            temp = append_str(temp, get_value(env, "HOME"));
        else
        {
            char c[2] = { line[i], '\0' };
            temp = append_str(temp, c);
        }
        i++;
    }
    return (temp);
}
