/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:14:32 by afarapon          #+#    #+#             */
/*   Updated: 2017/10/28 16:14:33 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(char *s1, char *s2, size_t n)
{
	while (*s1 == *s2 && *s1 && n--)
	{
		s1++;
		s2++;
	}
	if (n > 0)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	else
		return (0);
}
