/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:14:52 by afarapon          #+#    #+#             */
/*   Updated: 2017/11/05 23:45:49 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		*ft_strrchr(const char *s, int c)
{
	unsigned char *begin;
	unsigned char chr;
	unsigned char *end;

	chr = (unsigned char)c;
	begin = (unsigned char*)s;
	end = begin;
	while (*end)
		end++;
	while (end >= begin)
	{
		if (*end == chr)
			return ((char*)end);
		end--;
	}
	return (0);
}
