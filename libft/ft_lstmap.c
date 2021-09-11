/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 03:04:04 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/11 09:08:25 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*element;

	if (!f || !del)
		return (NULL);
	newlst = NULL;
	while (lst)
	{
		element = ft_lstnew(f(lst->content));
		if (!element)
		{
			while (newlst)
			{
				element = newlst->next;
				(*del)(newlst->content);
				free(newlst);
				newlst = element;
			}
		}
		lst = lst->next;
		ft_lstadd_back(&newlst, element);
	}
	return (newlst);
}
