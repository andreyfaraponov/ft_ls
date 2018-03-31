/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:14:56 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/28 16:14:56 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	size_t	i;
	size_t	len;
	char	temp;

	i = -1;
	len = ft_strlen(str);
	while (++i < --len)
	{
		temp = str[i];
		str[i] = str[len];
		str[len] = temp;
	}
	return (str);
}
