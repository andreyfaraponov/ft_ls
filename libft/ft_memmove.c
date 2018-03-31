/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:12:21 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/29 19:26:19 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*result;

	result = dest;
	if (dest > src)
	{
		dest += n;
		src += n;
		while (n--)
			*(unsigned char*)--dest = *(unsigned char*)--src;
	}
	else
		while (n--)
			*(unsigned char*)dest++ = *(unsigned char*)src++;
	return (result);
}
