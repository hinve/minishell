/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:09:28 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:19:20 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_isascii(int c)
{
	if (c >= '\0' && c <= '\177')
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
    int myValue = 'A'; 
    if (ft_isascii(myValue))
	{
        printf("%d is a valid ASCII character.\n", myValue);
    }
	else
	{
        printf("%d is not a valid ASCII character.\n", myValue);
    }
    return 0;
} */