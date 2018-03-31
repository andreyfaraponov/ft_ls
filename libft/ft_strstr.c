/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:15:52 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/29 19:28:36 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *where, const char *what)
{
	int		i;
	int		j;
	int		t;

	if (!ft_strlen(what))
		return ((char*)where);
	i = 0;
	while (where[i])
	{
		if (where[i] == what[0] && !(j = 0))
		{
			t = i;
			while (where[t] == what[j])
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
