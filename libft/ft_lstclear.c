/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 03:58:45 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/09 03:58:47 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*link;
	t_list	*tmp;

	link = *lst;
	while (link)
	{
		tmp = link->next;
		ft_lstdelone(link, del);
		link = tmp;
	}
	*lst = NULL;
}
