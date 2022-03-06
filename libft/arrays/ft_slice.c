/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:28:59 by jkasongo          #+#    #+#             */
/*   Updated: 2021/09/10 10:00:56 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/array_utils.h"

static int	*run_copy(int begin, int end, const int original[])
{
	int				i;
	int				j;
	int				*copy;

	i = 0;
	j = 0;
	copy = (int *)malloc(sizeof(int) * (end - begin));
	if (!copy)
		return (NULL);
	if (original)
	{
		while (original[i])
		{
			if ((i >= begin) && (i < end))
			{
				copy[j] = original[i];
				j++;
			}
			if (i == end)
				break ;
			i++;
		}
	}
	return (copy);
}

int	*ft_slice_int(const int original[], int begin, int end)
{
	unsigned int	size;
	int				*copy;

	size = end - begin;
	copy = NULL;
	if (size > 0)
		copy = run_copy(begin, end, original);
	return (copy);
}
