/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:17:31 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/13 16:54:17 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*heap_p;
	size_t	total_size;

	total_size = count * size;
	heap_p = malloc(total_size);
	if (heap_p == NULL)
		return (NULL);
	ft_bzero(heap_p, total_size);
	return (heap_p);
}
