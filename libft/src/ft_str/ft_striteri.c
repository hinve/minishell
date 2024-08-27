/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matta <matta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:36:28 by mjeannin          #+#    #+#             */
/*   Updated: 2024/06/21 13:29:39 by matta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
void	uppercase(unsigned int index, char *ch)
{
	*ch = ft_toupper(*ch);
	index = ft_strlen(ch);
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (s && f)
	{
		i = 0;
		while (*s)
			f(i++, s++);
	}
}
/*
int main()
{
	char	str[15] = "hola mundo";

	ft_striteri(str, uppercase);
	printf("%s\n", str);
	return (0);
}*/
