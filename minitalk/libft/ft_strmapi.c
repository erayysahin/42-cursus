/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:05:04 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/28 23:15:10 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*str;

	if (!s)
		return (0);
	len = ft_strlen(s);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (0);
	i = 0;
	while (i < len)
	{
		*(str + i) = *(s + i);
		*(str + i) = (*f)(i, *(str + i));
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
