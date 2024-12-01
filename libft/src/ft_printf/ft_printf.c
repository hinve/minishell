/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 20:46:20 by mjeannin          #+#    #+#             */
/*   Updated: 2024/01/09 10:33:23 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(char spec, va_list arp)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count += print_char(va_arg(arp, int));
	else if (spec == 's')
		count += print_str(va_arg(arp, char *));
	else if (spec == 'd')
		count += print_digit((long)(va_arg(arp, int)), 10);
	else if (spec == 'x')
		count += print_digit((long)(va_arg(arp, unsigned int)), 16);
	else if (spec == 'X')
		count += print_xdigit((long)(va_arg(arp, unsigned int)), 16);
	else if (spec == 'i')
		count += print_digit((long)(va_arg(arp, int)), 10);
	else if (spec == 'u')
		count += print_digit((unsigned int)(va_arg(arp, int)), 10);
	else if (spec == 'p')
		count += print_ptr((void *)va_arg(arp, void *));
	else
		count += write(1, &spec, 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	arp;
	int		count;

	if ((write(1, "", 0)) == -1)
		return (-1);
	va_start(arp, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			count += print_format(*(++format), arp);
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(arp);
	return (count);
}
/*
int	main(void)
{
	int	count;
	char	*min = "3078 6666 6666 6666 6666 6666 6666 6337";
	char	*max = "15236";

	count = ft_printf("\001\002\007\v\010\f\r\n");
	ft_printf("The chars written are %d\n", count);
	printf("\001\002\007\v\010\f\r\n");
	return (0);
}5*/