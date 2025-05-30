/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:25:01 by erasahin          #+#    #+#             */
/*   Updated: 2024/02/13 14:19:29 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_putchar(int ch)
{
	return (write(1, &ch, 1));
}

int	check_format(char ch)
{
	if (ch == 'c' || ch == 's' || ch == 'p' || ch == 'd' || ch == 'i'
		|| ch == 'u' || ch == 'x' || ch == 'X' || ch == '%')
		return (1);
	return (0);
}

int	printf_format(char ch, va_list lst)
{
	if (ch == 'c')
		return (ft_putchar(va_arg(lst, int)));
	else if (ch == '%')
		return (ft_putchar('%'));
	else if (ch == 's')
		return (ft_putstr(va_arg(lst, char *)));
	else if (ch == 'i' || ch == 'd')
		return (ft_putnbr(va_arg(lst, int), 0));
	else if (ch == 'p')
		return (ft_print_ptr(va_arg(lst, unsigned long), 42, 0));
	else if (ch == 'x' || ch == 'X')
		return (ft_print_hex(va_arg(lst, unsigned int), ch, 0));
	else if (ch == 'u')
		return (ft_print_unsigned(va_arg(lst, unsigned int), 0));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	lst;
	int		i;
	int		count;
	int		value;

	count = 0;
	i = -1;
	va_start(lst, format);
	while (format[++i])
	{
		if (format[i] == '%' && check_format(format[i + 1]))
		{
			value = printf_format(format[++i], lst);
			if (value == -1)
				return (-1);
			count += value;
		}
		else if (format[i] != '%' && ft_putchar(format[i]) == -1)
			return (-1);
		else if (format[i] != '%')
			count++;
	}
	va_end(lst);
	return (count);
}
