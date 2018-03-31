/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:11:43 by afarapon          #+#    #+#             */
/*   Updated: 2017/12/09 18:41:09 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*el;

	if (!(el = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		el->content = malloc(content_size);
		if (!el->content)
		{
			free(el);
			return (NULL);
		}
		ft_memcpy(el->content, content, content_size);
		el->content_size = content_size;
	}
	else
	{
		el->content = NULL;
		el->content_size = 0;
	}
	return (el);
}
