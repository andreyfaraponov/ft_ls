/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:14:45 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/28 16:14:45 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*result;

	if ((result = (char*)malloc(size + 1)))
	{
		result = ft_memset(result, '\0', size + 1);
		return (result);
	}
	return (NULL);
}
