/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:03:54 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/21 16:04:48 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char *ft_strcat(char *dest, const char *src)
{
    char *dest_ptr;

    dest_ptr = dest;
    while (*dest_ptr)
        dest_ptr++;
    while (*src)
        *dest_ptr++ = *src++;

    *dest_ptr = '\0';
    return (dest);
}