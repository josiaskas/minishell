/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 02:24:14 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/06 02:24:15 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	int	islower;
	int	isupper;

	islower = (c >= 97 && c <= 122);
	isupper = (c >= 65 && c <= 90);
	return (islower || isupper);
}
