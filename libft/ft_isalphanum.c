/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalphanum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:36:48 by afarapon          #+#    #+#             */
/*   Updated: 2017/11/06 00:55:28 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalphanum(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (ft_isalnum(*str))
			str++;
		else
			return (0);
	}
	return (1);
}
