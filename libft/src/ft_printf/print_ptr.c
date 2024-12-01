/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:37:41 by mjeannin          #+#    #+#             */
/*   Updated: 2024/01/08 15:29:37 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pdigit(unsigned long n, int base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (n < (unsigned long long)base)
	{
		return (print_char(symbols[n]));
	}
	else
	{
		count = print_pdigit(n / 16, base);
		return (count + print_pdigit(n % base, base));
	}
}

int	print_ptr(void *ptr)
{
	unsigned long	ptra;
	int				count;

	ptra = (unsigned long)ptr;
	write(1, "0x", 2);
	count = print_pdigit((unsigned long)ptra, 16) + 2;
	return (count);
}
