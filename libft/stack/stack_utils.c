/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 14:35:03 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/31 16:37:25 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

bool	swap(t_stack *stack)
{
	t_stack_node	*first;
	t_stack_node	*second;
	void			*temp;

	if (stack == 0)
		return (false);
	if (stack->length <= 1)
		return (false);
	first = stack->head;
	second = first->next;
	temp = first->content;
	first->content = second->content;
	second->content = temp;
	return (true);
}

bool	rotate(t_stack *stack)
{
	t_stack_node	*first;
	t_stack_node	*second;

	if (stack == 0)
		return (false);
	if (stack->length <= 1)
		return (false);
	if (stack->length == 2)
		return (swap(stack));
	first = stack->head;
	second = first->next;
	stack->head = second;
	stack->bottom = first;
	return (true);
}

bool	reverse_rotate(t_stack *stack)
{
	t_stack_node	*last;
	t_stack_node	*before_last;

	if (stack == 0)
		return (false);
	if (stack->length <= 1)
		return (false);
	if (stack->length == 2)
		return (swap(stack));
	last = stack->bottom;
	before_last = stack->head;
	while (before_last->next != last)
		before_last = before_last->next;
	stack->bottom = before_last;
	stack->head = last;
	return (true);
}

int	*map_stack(t_stack *stack, int (*apply)(void *, int index))
{
	int				*results;
	t_stack_node	*node;
	int				i;

	i = 0;
	if (!stack)
		return (0);
	if (!stack->length)
		return (0);
	results = malloc(sizeof(int) * (stack->length));
	if (!results)
		return (0);
	node = stack->head;
	while (i < stack->length)
	{
		results[i] = apply(node->content, i);
		node = node->next;
		i++;
	}
	return (results);
}

t_stack_node	*get_next(t_stack *stack)
{
	int				i;
	t_stack_node	*node;

	i = 0;
	node = stack->head;
	if (stack == 0)
		return (0);
	while ((i <= stack->length) && (i <= stack->current))
	{
		node = node->next;
		i++;
	}
	if (stack->current < stack->length)
		stack->current++;
	return (node);
}
