/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_malloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:06:06 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/16 17:07:35 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/srcs/libft.h"
#include "s_malloc.h"
#include <stdlib.h>

void	add_garbage_c(void *ptr)
{
	t_malloc	*garbage_c;

	if (!ptr)
		program_exit("MALLOC_ERROR", -1);
	garbage_c = get_garbage_c();
	while (garbage_c->next)
		garbage_c = garbage_c->next;
	garbage_c->next = ft_calloc(1, sizeof(t_malloc));
	if (!garbage_c->next)
	{
		free(ptr);
		program_exit("MALLOC_ERROR", -1);
	}
	*garbage_c->next = (t_malloc){.ptr = ptr, .next = NULL};
}

void	garbage_collecter(void *ptr)
{
	t_malloc	*garbage_c;
	t_malloc	*tmp;

	if (!ptr)
		return ;
	tmp = NULL;
	garbage_c = get_garbage_c();
	while (garbage_c)
	{
		if (garbage_c->ptr == ptr)
		{
			tmp->next = garbage_c->next;
			free(garbage_c);
			return ;
		}
		tmp = garbage_c;
		garbage_c = garbage_c->next;
	}
}

void	gc_free(void)
{
	t_malloc	*tmp;
	t_malloc	*garbage_c;

	tmp = NULL;
	garbage_c = get_garbage_c()->next;
	while (garbage_c)
	{
		tmp = garbage_c;
		garbage_c = garbage_c->next;
		if (tmp->ptr)
			free(tmp->ptr);
		free(tmp);
	}
}
