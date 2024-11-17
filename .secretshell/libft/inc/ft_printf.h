/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:15:12 by mjeannin          #+#    #+#             */
/*   Updated: 2024/05/13 15:02:44 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);
int		ft_isalpha(int c);
int		print_char(int c);
int		print_str(char *str);
int		print_digit(long n, int base);
int		print_xdigit(long n, int base);
int		print_ptr(void *n);

#endif