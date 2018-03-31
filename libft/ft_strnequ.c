/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:14:40 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/29 15:58:26 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 && s2)
	{
		while (n > 0 && *s1 && *s2)
		{
			if (*s1 == *s2 && n--)
			{
				s1++;
				s2++;
			}
			else
				return (0);
		}
		return (1);
	}
	return (0);
}
