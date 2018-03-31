/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:11:49 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/28 16:16:27 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t n)
{
	void	*result;

	if ((result = malloc(n)))
	{
		ft_bzero(result, n);
		return (result);
	}
	return (NULL);
}
