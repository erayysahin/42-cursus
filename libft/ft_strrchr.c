/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:05:18 by erasahin          #+#    #+#             */
/*   Updated: 2023/12/27 15:39:21 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	a;

	a = (int)ft_strlen(s);
	while (a >= 0)
	{
		if (s[a] == (char)c)
			return ((char *)(s + a));
		a--;
	}
	return (0);
}
