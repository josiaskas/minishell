/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:09:41 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/08 23:14:56 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

t_stack	*create_stack(void)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (stack == 0)
		return (0);
	stack->length = 0;
	stack->head = 0;
	stack->bottom = 0;
	stack->current = 0;
	return (stack);
}

bool	push(t_stack *stack, void *content)
{
	t_stack_node	*node;

	if (!stack)
		return (false);
	node = (t_stack_node *)malloc(sizeof(t_stack_node));
	if (!node)
		return (false);
	node->content = content;
	if (stack->length == 0)
	{
		stack->bottom = node;
		stack->length = 1;
	}
	else
	{
		node->next = stack->head;
		stack->bottom->next = node;
		stack->length++;
	}
	stack->head = node;
	return (true);
}

void	*pop(t_stack *stack)
{
	t_stack_node	*node;
	void			*content;

	if (!stack)
		return (0);
	if (!stack->length)
		return (0);
	content = 0;
	node = stack->head;
	if (stack->length == 1)
	{
		content = node->content;
		stack->bottom = 0;
		stack->head = 0;
	}
	if (stack->length > 1)
	{	
		content = node->content;
		stack->bottom->next = stack->head->next;
		stack->head = stack->head->next;
	}
	stack->length--;
	free(node);
	return (content);
}

void	*peak(t_stack *stack)
{
	void	*content;

	if (!stack)
		return (0);
	if (!stack->length)
		return (0);
	content = stack->head->content;
	return (content);
}

bool	for_each_s(t_stack *stack, void (*apply)(void *, int index))
{
	t_stack_node	*node;
	int				i;

	i = 0;
	if (!stack)
		return (false);
	if (!stack->length)
		return (false);
	node = stack->head;
	while (i < stack->length)
	{
		apply(node->content, i);
		node = node->next;
		i++;
	}
	return (true);
}
