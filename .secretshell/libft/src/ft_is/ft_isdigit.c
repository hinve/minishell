/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:09:18 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:19:29 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_isdigit(int i)
{
	if (i <= '9' && i >= '0')
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
    char myChar = 'd';
    if (ft_isdigit(myChar))
	{
        printf("%c is a decimal digit.\n", myChar);
    } else {
        printf("%c is not a decimal digit.\n", myChar);
    }
    return 0;
}*/
