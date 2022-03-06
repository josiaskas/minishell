/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 21:42:04 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/07 21:43:36 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(void **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != 0)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
