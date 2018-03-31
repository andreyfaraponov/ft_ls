/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:12:04 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/29 09:26:55 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*one;
	unsigned char	*two;

	one = (unsigned char*)s1;
	two = (unsigned char*)s2;
	while (n--)
	{
		if (*one != *two)
			return (*one - *two);
		one++;
		two++;
	}
	return (0);
}
