/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_malloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:05:46 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/11 13:05:55 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_MALLOC_H
# define S_MALLOC_H

typedef struct s_malloc
{
	void			*ptr;
	struct s_malloc	*next;
}					t_malloc;

void				add_garbage_c(void *ptr);
void				garbage_collecter(void *ptr);
void				gc_free(void);
t_malloc			*get_garbage_c(void);
void				*gc_malloc(unsigned int size);
void				safe_free(void *ptr);

#endif