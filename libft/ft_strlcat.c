/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:04:52 by erasahin          #+#    #+#             */
/*   Updated: 2023/12/27 15:39:48 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dststart;
	size_t	a;
	size_t	srclen;

	dststart = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dststart + 1 > dstsize)
		return (dstsize + srclen);
	a = 0;
	while (src[a] && a + dststart < dstsize - 1)
	{
		dst[dststart + a] = src[a];
		a++;
	}
	dst[dststart + a] = '\0';
	return (dststart + srclen);
}
