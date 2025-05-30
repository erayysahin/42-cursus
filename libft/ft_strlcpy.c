/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:04:56 by erasahin          #+#    #+#             */
/*   Updated: 2023/12/27 15:39:46 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	a;

	a = 0;
	if (dstsize > 0)
	{
		while (*src && a + 1 < dstsize)
		{
			*dst++ = *src++;
			a++;
		}
	}
	if (a < dstsize)
		*dst = '\0';
	while (*src++)
		a++;
	return (a);
}
