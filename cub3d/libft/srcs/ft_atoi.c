/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:46:08 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/25 15:37:16 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_utils(const char *str, int *s)
{
	while (*str != '\0' && *str != '\n' && *str != ',')
	{
		if (*str >= '0' && *str <= '9')
		{
			*s = *s * 10 + (*str - '0');
			str++;
		}
		else if (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\v'
			|| *str == '\f')
			str++;
		else
			return (1);
	}
	return (0);
}

int	ft_atoi(const char *str, int *data)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (*str && i < 3)
	{
		s = 0;
		if (!(*str >= '0' && *str <= '9') && !(*str == ' ' || *str == '\t'
				|| *str == '\r' || *str == '\v' || *str == '\f'))
			return (1);
		if (ft_atoi_utils(str, &s))
			return (1);
		data[i++] = s;
		if (*str != '\0' && *str == ',')
			str++;
	}
	return (0);
}
