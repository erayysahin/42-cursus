/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:04:05 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/28 23:14:22 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * n);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(tmp + i) = *(const char *)(src + i);
		i++;
	}
	i = 0;
	while (i < n)
	{
		*(char *)(dst + i) = *(tmp + i);
		i++;
	}
	free(tmp);
	return (dst);
}
