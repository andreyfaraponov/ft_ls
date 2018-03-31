/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:14:49 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/28 20:17:26 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *where, const char *what, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	t;

	i = 0;
	if (!ft_strlen((char*)what))
		return ((char*)where);
	while (where[i] && i < n)
	{
		if (where[i] == what[0] && !(j = 0))
		{
			t = i;
			while (what[j] && where[t] && where[t] == what[j] && t < n)
			{
				t++;
				j++;
				if (what[j] == '\0')
					return ((char*)(where + i));
			}
		}
		i++;
	}
	return (0);
}
