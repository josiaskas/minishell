/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 17:55:56 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/28 12:08:31 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/array_utils.h"

bool	is_sorted_asc(int arr[], int n)
{
	bool	status;
	int		i;

	i = 0;
	status = false;
	while (i < (n - 1))
	{
		if (arr[i] > arr[i + 1])
			break ;
		i++;
	}
	if (i == (n - 1))
		status = true;
	return (status);
}

bool	is_sorted_desc(int arr[], int n)
{
	bool	status;
	int		i;

	i = 0;
	status = false;
	while (i < (n - 1))
	{
		if (arr[i] < arr[i + 1])
			break ;
		i++;
	}
	if (i == (n - 1))
		status = true;
	return (status);
}

int	type_of_sort(int arr[], int n)
{
	if (is_sorted_asc(arr, n))
		return (1);
	if (is_sorted_desc(arr, n))
		return (2);
	return (3);
}
