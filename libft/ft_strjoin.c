/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:14:03 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/29 15:53:47 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;

	if (s1 && s2)
	{
		if ((result = ft_strnew(ft_strlen((char*)s1) + ft_strlen((char*)s2)))
		== NULL)
			return (NULL);
		result = ft_strcat(result, (char*)s1);
		result = ft_strcat(result, (char*)s2);
		return (result);
	}
	return (NULL);
}
