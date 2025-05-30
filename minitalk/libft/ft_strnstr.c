/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:05:13 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/28 23:15:14 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;
	size_t	b;

	if (!little[0])
		return ((char *)big);
	a = 0;
	while (big[a])
	{
		b = 0;
		while (big[a + b] == little[b] && a + b < len)
		{
			if (!big[a + b] || !little[b])
			{
				return ((char *)big + a);
			}
			b++;
		}
		if (!little[b])
		{
			return ((char *)big + a);
		}
		a++;
	}
	return (0);
}
