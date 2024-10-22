/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup .c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matta <matta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:05:26 by mjeannin          #+#    #+#             */
/*   Updated: 2024/10/18 11:33:37 by matta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strndup(const char *source, size_t n)
{
	char	*dup;
	int		len;

	dup = (char *)malloc(ft_strlen(source) + 1);
	if (source == NULL)
	{
		return (NULL);
	}
	if (dup != NULL)
	{
		ft_strlcpy(dup, source, ft_strlen(source) + 1);
	}
	return (dup);
}


    