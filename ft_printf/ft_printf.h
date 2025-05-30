/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:09:13 by erasahin          #+#    #+#             */
/*   Updated: 2024/02/07 14:54:21 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_putchar(int ch);
int	ft_putnbr(int number, int count);
int	ft_putstr(char *s);
int	ft_print_ptr(unsigned long n, int firstCall, int number);
int	ft_print_hex(unsigned long n, char ch, int number);
int	ft_print_unsigned(unsigned int n, int number);
int	ft_printf(const char *format, ...);

#endif