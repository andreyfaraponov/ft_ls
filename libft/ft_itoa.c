/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:11:15 by afarapon          #+#    #+#             */
/*   Updated: 2017/11/07 00:34:04 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_digitcount(unsigned int n)
{
	int				count;

	count = 0;
	while (n / 10 && (++count))
		n /= 10;
	return (++count);
}

char			*ft_itoa(int n)
{
	int				sign;
	char			*res;
	unsigned int	z;
	int				len;

	sign = (n < 0) ? -1 : 1;
	len = ft_digitcount(n * sign);
	len += (sign < 0) ? 1 : 0;
	if ((res = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	ft_bzero((void*)res, len + 1);
	z = (unsigned int)(n * sign);
	if (sign == -1)
		res[0] = '-';
	res[len--] = '\0';
	while (len >= 0)
	{
		if (res[len] != '-')
			res[len--] = (z % 10) + '0';
		else
			len--;
		z /= 10;
	}
	return (res);
}
