/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 08:40:08 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/28 15:01:07 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

void	pb(t_stack *stack, int print)
{
	int	index;

	index = 0;
	if (stack->size_a)
	{
		stack->size_b++;
		index = stack->size_b;
		while (--index > 0)
			stack->b[index] = stack->b[index - 1];
		stack->b[0] = stack->a[0];
		index = -1;
		stack->size_a--;
		while (++index < stack->size_a)
			stack->a[index] = stack->a[index + 1];
		if (!print)
			write(1, "pb\n", 3);
	}
	else
		return ;
}

void	sb(t_stack	*stack, int print)
{
	int	tmp;

	tmp = 0;
	if (stack->size_b < 2)
		return ;
	tmp = stack->b[0];
	stack->b[0] = stack->b[1];
	stack->b[1] = tmp;
	if (!print)
		write(1, "sb\n", 3);
}

void	rb(t_stack	*stack, int print)
{
	int	tmp;
	int	index;

	index = 0;
	tmp = stack->b[index];
	index++;
	while (index < stack->size_b)
	{
		stack->b[index - 1] = stack->b[index];
		index++;
	}
	stack->b[index - 1] = tmp;
	if (!print)
		write(1, "rb\n", 3);
}

void	rrb(t_stack *stack, int print)
{
	int	tmp;
	int	index;

	index = stack->size_b - 1;
	tmp = stack->b[index];
	while (index)
	{
		stack->b[index] = stack->b[index - 1];
		index--;
	}
	stack->b[index] = tmp;
	if (!print)
		write(1, "rrb\n", 4);
}
