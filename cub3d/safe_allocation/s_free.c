/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:00:22 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/11 15:43:07 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/srcs/libft.h"
#include "s_malloc.h"
#include <stdlib.h>

t_malloc	*get_garbage_c(void)
{
	static t_malloc	garbage_c = {NULL, NULL};

	return (&garbage_c);
}

void	*gc_malloc(unsigned int size)
{
	void		*ptr;
	t_malloc	*garbage_c;

	garbage_c = get_garbage_c();
	while (garbage_c->next)
		garbage_c = garbage_c->next;
	garbage_c->next = ft_calloc(1, sizeof(t_malloc));
	if (!garbage_c->next)
		program_exit("MALLOC_ERROR", -1);
	ptr = ft_calloc(1, size);
	if (!ptr)
		program_exit("MALLOC_ERROR", -1);
	*garbage_c->next = (t_malloc){.ptr = ptr, .next = NULL};
	return (ptr);
}

void	safe_free(void *ptr)
{
	if (!ptr)
		return ;
	garbage_collecter(ptr);
	free(ptr);
}
