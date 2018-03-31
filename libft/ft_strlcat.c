/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:14:07 by afarapon          #+#    #+#             */
/*   Updated: 2017/11/05 02:52:23 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t		size;

	size = (size_t)(ft_strlen(dest) + ft_strlen((char*)src));
	if (ft_strlen(dest) >= n)
		return (ft_strlen((char*)src) + n);
	n = n - ft_strlen(dest) - 1;
	while (*dest)
		dest++;
	while (*(unsigned char*)src && n)
	{
		*(unsigned char*)dest++ = *(unsigned char*)src++;
		n--;
	}
	*dest = '\0';
	return (size);
}
