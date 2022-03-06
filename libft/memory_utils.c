/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 14:22:27 by jkasongo          #+#    #+#             */
/*   Updated: 2021/09/28 13:23:18 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(void **array, size_t size)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
	return ;
}

void	free_stack(t_stack *stack)
{
	void	*content;

	if (!stack)
		return ;
	while (stack->length)
	{
		content = pop(stack);
		free(content);
	}
	free(stack);
	stack = NULL;
	return ;
}

void	ft_free_splitted(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}
