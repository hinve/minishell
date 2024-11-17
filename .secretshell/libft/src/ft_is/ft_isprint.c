/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:09:31 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:19:34 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
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
    char myChar = 'A';
    if (ft_isprint(myChar))
	{
        printf("%c is a printable character.\n", myChar);
    } else {
        printf("%c is not a printable character.\n", myChar);
    }
    return 0;
} */