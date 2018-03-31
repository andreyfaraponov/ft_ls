/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:15:56 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/29 15:57:41 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*result;

	if (s)
	{
		if ((result = (char*)malloc(len + 1)) == NULL)
			return (NULL);
		result = ft_strncpy(result, s + start, len);
		result[len] = '\0';
		return (result);
	}
	return (NULL);
}
