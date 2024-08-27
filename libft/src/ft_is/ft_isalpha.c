/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:09:24 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:19:14 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_isalpha(int c)
{
	if ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/*
 int main()
 {
    char myChar = '3';
    if (ft_isalpha(myChar))
	{
        printf("%c is an alphabetic character.\n", myChar);
    }
	else
	{
        printf("%c is not an alphabetic character.\n", myChar);
    }
    return 0;
} */
