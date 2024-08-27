/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:09:42 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:21:12 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	uc;

	p = s;
	uc = c;
	while (n-- > 0)
	{
		*p++ = uc;
	}
	return (s);
}
/*
int main()
{
    char myString[20];

    ft_memset(myString, 'A', sizeof(myString));

    printf("myString: %s\n", myString);
    return 0;
} */