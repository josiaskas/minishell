/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 02:50:34 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/09 03:20:28 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*begin;

	if ((!lst) || (!f) || (!del))
		return (0);
	newlst = ft_lstnew(f(lst->content));
	if (!newlst)
		return (0);
	begin = newlst;
	lst = lst->next;
	while (lst)
	{
		newlst->next = ft_lstnew(f(lst->content));
		if (!newlst->next)
		{
			ft_lstclear(&begin, del);
			return (0);
		}
		lst = lst->next;
		newlst = newlst->next;
	}
	return (begin);
}
