/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:14:10 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/29 16:43:06 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t		result;

	if (dest && src)
	{
		result = (size_t)ft_strlen((char*)src);
		while (*src && (n - 1))
		{
			*(dest++) = *(src++);
			n--;
		}
		*dest = '\0';
		return (result);
	}
	return (0);
}
