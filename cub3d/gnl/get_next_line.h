/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:33:28 by osarikay          #+#    #+#             */
/*   Updated: 2024/12/18 15:49:49 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup2(const char *buffer);
char	*ft_strjoin(char const *stack, char const *buffer);
char	*ft_substr(char const *stack, unsigned int start, size_t len);
void	*ft_free_stack(char **stack, int create_line);

#endif