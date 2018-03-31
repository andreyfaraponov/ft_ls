/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:11:54 by afarapon          #+#    #+#             */
/*   Updated: 2017/11/04 23:13:54 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c,
	size_t n)
{
	unsigned char *ddst;
	unsigned char *ssrc;

	ddst = (unsigned char*)dest;
	ssrc = (unsigned char*)src;
	while (n--)
		if ((*ddst++ = *ssrc++) == (unsigned char)c)
			return ((void*)(ddst));
	return (0);
}
