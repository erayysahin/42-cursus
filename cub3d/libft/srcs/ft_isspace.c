/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:46:52 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/11 17:46:55 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] <= 13 && str[i] >= 7)))
		i++;
	return (i);
}
