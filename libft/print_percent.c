/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 21:29:34 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/08 12:36:09 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_print_percent(char **f, t_all_flags flags)
{
	char	*res;

	(*f)++;
	res = ft_strnew(1);
	res[0] = '%';
	res = ft_make_width_char(res, flags);
	return (res);
}
