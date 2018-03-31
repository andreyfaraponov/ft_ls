/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:11:36 by afarapon          #+#    #+#             */
/*   Updated: 2017/11/04 14:36:03 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_deleteelem(void *cont, size_t len)
{
	free(cont);
	(void)len;
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *result;
	t_list *tempnext;

	if (!lst || !f)
		return (NULL);
	result = f(lst);
	lst = lst->next;
	tempnext = result;
	while (lst)
	{
		tempnext->next = f(lst);
		if (tempnext->next && result)
			tempnext = tempnext->next;
		else
			while (result)
			{
				tempnext = result->next;
				ft_lstdelone(&result, ft_deleteelem);
				result = tempnext;
			}
		lst = lst->next;
	}
	return (result);
}
