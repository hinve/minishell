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

char *get_env_var(char *line, int *i, t_env *env)
{
    int start = *i + 1;
    while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
        (*i)++;
    char *var_name = ft_substr(line, start, *i - start);
    char *value = get_value(env, var_name);
    free(var_name);
    return value ? value : "";
}

char *expand_heredoc(char *line, t_env *env)
{
    int i = 0;
    char *temp = ft_strdup("");
    while (line && line[i])
    {
        if (line[i] == '$')
        {
            char *value = get_env_var(line, &i, env);
            temp = append_str(temp, value);
        }
        else if (line[i] == '~' && (!line[i + 1] || line[i + 1] == '/'))
        {
            temp = append_str(temp, get_value(env, "HOME"));
            i++;
        }
        else
        {
            char c[2] = { line[i], '\0' };
            temp = append_str(temp, c);
            i++;
        }
    }
    return (temp);
}
