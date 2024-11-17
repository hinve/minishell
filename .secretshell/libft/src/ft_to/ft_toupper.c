/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:10:01 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:23:28 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_toupper(int c)
{
	if (c <= 'z' && c >= 'a')
	{
		c -= 32;
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
	char c = 'd';
	c = toupper(c);
	printf("%c", c);
	return (0);
}*/