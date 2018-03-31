/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:16:00 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/29 19:27:02 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcount(const char *s, int c)
{
	int		i;
	int		res;

	res = 0;
	i = 0;
	if (s)
		while (s[i])
		{
			if (s[i] == (char)c)
				res = i;
			i++;
		}
	return (res);
}

char		*ft_strtrim(char const *s)
{
	char		*end;

	if (s)
	{
		while ((*s == ' ' || *s == '\n' || *s == '\t') && *s)
			s++;
		end = (char*)s + ft_strlen((char*)s) - 1;
		while (*end == ' ' || *end == '\n' || *end == '\t')
			end--;
		return (ft_strsub(s, 0, ft_strcount(s, *end) + 1));
	}
	return (NULL);
}
