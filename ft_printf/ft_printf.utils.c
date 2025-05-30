/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:24:22 by erasahin          #+#    #+#             */
/*   Updated: 2024/02/08 14:19:08 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	while (s[count])
	{
		if (ft_putchar(s[count++]) == -1)
			return (-1);
	}
	return (count);
}

int	ft_putnbr(int number, int count)
{
	if (number == -2147483648)
	{
		return (ft_putstr("-2147483648"));
	}
	else if (number < 0)
	{
		count += ft_putchar('-');
		if (count == -1)
			return (-1);
		count = ft_putnbr(-number, count);
	}
	else if (number >= 10)
	{
		count = ft_putnbr(number / 10, count);
		if (count == -1)
			return (-1);
		count = ft_putnbr(number % 10, count);
	}
	else
	{
		count += ft_putchar(number + '0');
		if (count == -1)
			return (-1);
	}
	return (count);
}

int	ft_print_ptr(unsigned long n, int firstCall, int number)
{
	if (firstCall == 42)
	{
		number += ft_putstr("0x");
		if (number == -1)
			return (-1);
		number = ft_print_ptr(n, 0, number);
	}
	else
	{
		if (n >= 16)
			number = ft_print_ptr(n / 16, 0, number);
		number += ft_putchar("0123456789abcdef"[n % 16]);
		if (number == -1)
			return (-1);
	}
	return (number);
}

int	ft_print_hex(unsigned long n, char ch, int number)
{
	if (n >= 16)
	{
		number = ft_print_hex(n / 16, ch, number);
		if (number == -1)
			return (-1);
	}
	if (ch == 'x')
	{
		number += ft_putchar("0123456789abcdef"[n % 16]);
		if (number == -1)
			return (-1);
	}
	else
	{
		number += ft_putchar("0123456789ABCDEF"[n % 16]);
		if (number == -1)
			return (-1);
	}
	return (number);
}

int	ft_print_unsigned(unsigned int n, int number)
{
	if (n >= 10)
	{
		number = ft_print_unsigned(n / 10, number);
		if (number == -1)
			return (-1);
		number = ft_print_unsigned(n % 10, number);
	}
	else
	{
		number += ft_putchar(n + '0');
		if (number == -1)
			return (-1);
	}
	return (number);
}
