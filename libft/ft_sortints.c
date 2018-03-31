/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 11:51:43 by afarapon          #+#    #+#             */
/*   Updated: 2017/11/04 13:42:07 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_sortints(int src[], size_t n, int (*sort)(int el1, int el2))
{
	size_t		i;
	size_t		j;

	if (!src || !n || !sort)
		return ;
	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (sort(src[i], src[j]))
				ft_swap(&src[i], &src[j]);
			j++;
		}
		i++;
	}
}
