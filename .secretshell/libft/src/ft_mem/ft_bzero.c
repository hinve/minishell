/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:09:14 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/15 14:20:43 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
/*
int	main()
{
	char	str[10] = "0123456789";
	size_t	n = 5;
	printf("el resultado antes de la funcion : %s\n", str);
	ft_bzero(str, n);
	printf("el resultado despues de la funcion : %s", str);
	return (0);
}*/