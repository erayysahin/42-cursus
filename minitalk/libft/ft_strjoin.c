/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:04:48 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/28 23:15:01 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	int		s2len;
	int		s1len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	temp = (char *)malloc(s1len + s2len + 1);
	temp[0] = '\0';
	ft_strlcat(temp, s1, s1len + 1);
	ft_strlcat(temp + s1len, s2, s2len + 1);
	return (temp);
}
