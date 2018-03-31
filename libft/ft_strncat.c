/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:14:28 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/28 21:37:54 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*res;
	char	temp;

	res = dest;
	while (*dest)
		dest++;
	while (n-- && *src)
	{
		temp = *src;
		*dest = temp;
		dest++;
		src++;
	}
	*dest = '\0';
	return (res);
}
