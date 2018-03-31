/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 21:39:54 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/08 12:35:53 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_get_hex(t_all_flags all, va_list list, char system)
{
	char		*num;
	uintmax_t	sig;

	if (all.hh)
		sig = (unsigned char)va_arg(list, unsigned int);
	else if (all.h)
		sig = (unsigned short int)va_arg(list, unsigned int);
	else if (all.l)
		sig = va_arg(list, unsigned long int);
	else if (all.ll)
		sig = va_arg(list, unsigned long long int);
	else if (all.j)
		sig = va_arg(list, uintmax_t);
	else if (all.z)
	{
		num = ft_itoa_base(va_arg(list, size_t), system, all);
		return (ft_hex_make(num, all, ft_strcmp("0", num)));
	}
	else
		sig = va_arg(list, unsigned int);
	num = ft_itoa_base(sig, system, all);
	return (ft_hex_make(num, all, ft_strcmp("0", num)));
}

char		*ft_get_hex_any(char **f, t_all_flags all, va_list list,
	char system)
{
	if (**f == 'X')
		all.large = 1;
	(*f)++;
	return (ft_get_hex(all, list, system));
}

static char	*ft_helper(char *src, t_all_flags all, char *sign)
{
	char	*temp;

	if (all.f_minus || !all.f_zero)
	{
		if (all.dot)
			src = ft_make_precision(src, all);
		temp = src;
		src = ft_strjoin(sign, src);
		src = ft_make_width(src, all);
	}
	else
	{
		all.width = all.width - 2;
		src = ft_make_precision(src, all);
		src = ft_make_width(src, all);
		temp = src;
		src = ft_strjoin(sign, src);
	}
	free(temp);
	return (src);
}

char		*ft_hex_make(char *src, t_all_flags all, int cmp_result)
{
	char	*sign;

	all.f_zero = all.dot ? 0 : all.f_zero;
	sign = ft_get_hex_sign(all);
	if (sign && cmp_result)
		src = ft_helper(src, all, sign);
	else if (!cmp_result && all.dot && !all.currency)
	{
		free(src);
		src = ft_strdup("");
		src = ft_make_width(src, all);
	}
	else
	{
		src = ft_make_precision(src, all);
		src = ft_make_width(src, all);
	}
	if (sign && all.f_sharp)
		free(sign);
	return (src);
}
