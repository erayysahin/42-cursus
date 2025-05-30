/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:48:31 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/11 17:48:32 by erasahin         ###   ########.fr       */
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
