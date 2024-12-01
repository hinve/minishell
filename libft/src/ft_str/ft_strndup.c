/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:05:26 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/01 18:09:59 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strndup(const char *source, size_t n)
{
	char	*dup;
	size_t	len;

	if (source == NULL)
	{
		return (NULL);
	}
	len = ft_strlen(source);
	if (len > n)
		len = n;
	dup = (char *)malloc(len + 1);
	if (dup != NULL)
	{
		ft_strlcpy(dup, source, len + 1);
	}
	return (dup);
}
