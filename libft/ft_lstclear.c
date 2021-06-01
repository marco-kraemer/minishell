/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 02:37:02 by maraurel          #+#    #+#             */
/*   Updated: 2021/02/12 19:40:59 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	new = *lst;
	while (new)
	{
		tmp = new;
		new = tmp->next;
		ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}
