/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:14:24 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/29 15:58:51 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	i = 0;
	if (s)
	{
		if ((result = ft_strdup((char*)s)) == NULL)
			return (NULL);
		while (result[i])
		{
			result[i] = f(i, result[i]);
			i++;
		}
		return (result);
	}
	return (NULL);
}
