/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 21:34:33 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/08 12:35:57 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_all_flags			ft_if_dot(char **src, t_all_flags all, char *sign,
	int isneg)
{
	t_all_flags		res_all;

	res_all = all;
	res_all.f_zero = 0;
	if (isneg)
		*sign = '-';
	if (res_all.width <= res_all.currency)
		res_all.width = 0;
	if (*sign && *sign != '-' && res_all.f_plus)
	{
		*sign = '+';
		if (res_all.f_minus)
			res_all.width--;
	}
	if (!ft_strcmp("0", *src))
	{
		free(*src);
		*src = ft_strnew(0);
	}
	return (res_all);
}

char				*ft_get_lint(t_all_flags all, va_list list)
{
	if ((!all.ll && !all.j && !all.z) && ft_size_flags_null(&all))
	{
		all.l = 1;
		return (ft_get_int(all, list));
	}
	return (ft_get_int(all, list));
}

char				*ft_get_int(t_all_flags all, va_list list)
{
	char		*num;
	ssize_t		sig;
	char		sign;

	if (all.hh)
		sig = (char)va_arg(list, int);
	else if (all.h)
		sig = (short)va_arg(list, int);
	else if (all.l)
		sig = va_arg(list, long int);
	else if (all.ll)
		sig = va_arg(list, long long int);
	else if (all.j)
		sig = va_arg(list, intmax_t);
	else if (all.z)
		sig = va_arg(list, ssize_t);
	else
		sig = va_arg(list, int);
	num = ft_itoa_base(ABS(sig), 10, all);
	sign = ft_get_sign(all, (sig < 0 ? 1 : 0));
	return (ft_numstr_make(num, all, (sig < 0 ? 1 : 0), sign));
}

char				*ft_numstr_make(char *src, t_all_flags all,
	int isneg, char sign)
{
	char	*temp;

	if (all.dot)
		all = ft_if_dot(&src, all, &sign, isneg);
	src = ft_make_precision(src, all);
	if ((sign == '-' && all.f_minus) || (sign == ' ' &&
		all.f_space && !all.dot))
		all.width--;
	src = ft_make_width(src, all);
	temp = src;
	if (sign && (((!all.f_space && !all.f_plus && !all.dot && sign != '-') ||
			all.currency == (intmax_t)ft_strlen(src)) ||
			(!all.f_zero && all.f_plus && !isneg && (!all.dot ||
					(all.width > all.currency && all.f_minus)))))
	{
		src = ft_strjoin(" ", src);
		src[0] = sign;
		free(temp);
	}
	else if (all.f_plus || ((sign == '-' || all.f_space) && !all.dot))
		src = ft_putsign(src, sign, all, isneg);
	else if (sign == '-')
		src = ft_putsign(src, sign, all, 1);
	return (src);
}
