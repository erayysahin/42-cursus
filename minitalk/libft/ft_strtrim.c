/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:05:25 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/28 23:15:31 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (ft_strchr(set, *s1) && *s1)
		s1++;
	i = ft_strlen(s1) - 1;
	while (i && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}
