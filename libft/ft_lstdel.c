/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:11:24 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/29 19:32:40 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*temp;

	if (*alst == NULL || del == NULL)
		return ;
	while (*alst)
	{
		temp = (*alst)->next;
		ft_lstdelone(alst, del);
		if (!temp)
			return ;
		(*alst) = temp;
	}
}
