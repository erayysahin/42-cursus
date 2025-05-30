/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:47:15 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/11 17:47:17 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return (NULL);
	if (dst < src)
		ft_memcpy(dst, src, n);
	else if (dst > src)
	{
		while (n--)
			*((unsigned char *)(dst + n)) = *((unsigned char *)(src + n));
	}
	return (dst);
}
