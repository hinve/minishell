/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:09:57 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:23:24 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_tolower(int c)
{
	if (c <= 'Z' && c >= 'A')
	{
		c = c + 32;
		return (c);
	}
	else
	{
		return (c);
	}
}
/*
int main()
{
	char c = 'D';
	c = ft_tolower(c);
	printf("%c", c);
	return (0);
}*/