/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 12:04:25 by jkasongo          #+#    #+#             */
/*   Updated: 2021/09/15 15:21:43 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_UTILS_H
# define ARRAY_UTILS_H
# include <stdbool.h>
# include <stdlib.h>

// Check if an array of int is sorted asc
bool	is_sorted_asc(int arr[], int n);
// Check if an array of int is sorted desc
bool	is_sorted_desc(int arr[], int n);
// return  1 if is asc, 2 is desc, 3 is not sorted
int		type_of_sort(int arr[], int n);

// return a copy of array from begin to end for int arrays
int		*ft_slice_int(const int original[], int begin, int end);
#endif
