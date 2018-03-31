/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 19:36:20 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/08 12:36:32 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_precision(char **f, va_list list)
{
	int		sign;
	int		res;

	sign = 1;
	res = 0;
	if (**f == '+')
		(*f)++;
	else if (**f == '-')
	{
		sign = -1;
		(*f)++;
	}
	if (**f == ' ')
		while (**f == ' ')
			(*f)++;
	if (**f == '*' && ++(*f))
	{
		res = va_arg(list, int);
		res = res < 0 ? 0 : res;
	}
	else if (ft_strchr("-+0123456789", **f))
		res = ft_get_number(f, sign);
	return (res);
}

static int	ft_get_width(char **f, va_list list)
{
	int		res;

	if (**f == '*')
	{
		(*f)++;
		res = va_arg(list, int);
	}
	else
		res = ft_get_number(f, 1);
	return (res);
}

int			ft_calcandprint(char **f, va_list list)
{
	t_all_flags	all_flags;
	int			result;

	result = 0;
	ft_all_flags_init(&all_flags);
	if (**f && ft_strchr("#+-0 ", **f))
		ft_get_flags(f, &all_flags);
	if (**f && ft_strchr("0123456789* ", **f))
		all_flags.width = ft_get_width(f, list);
	if (**f && ft_strchr(".", **f) && (*f)++ && ++all_flags.dot)
		all_flags.currency = ft_get_precision(f, list);
	if (**f && ft_strchr("hljz", **f))
		ft_get_size(f, &all_flags);
	return (ft_main_print(f, all_flags, list, &result));
}
