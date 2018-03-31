/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 21:30:04 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/08 12:36:24 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_putusign(char *src, char sign, t_all_flags all)
{
	char *temp;
	char *str_sign;

	temp = src;
	if (*src == ' ' && sign != ' ')
	{
		while (*src == ' ')
			src++;
		*(src - 1) = sign;
	}
	else if (sign == '+' && *src == '0')
		*src = sign;
	else if ((!all.dot || all.f_plus) && sign != ' ')
	{
		str_sign = ft_strnew(1);
		str_sign[0] = sign;
		temp = ft_strjoin(str_sign, src);
		free(src);
		free(str_sign);
	}
	return (temp);
}

static char	*ft_numustr_make(char *src, t_all_flags all)
{
	char	sign;
	char	*temp;

	sign = ft_get_sign(all, 0);
	if (all.dot)
		all = ft_if_dot(&src, all, &sign, 0);
	src = ft_make_precision(src, all);
	src = ft_make_width(src, all);
	temp = src;
	if (sign && (((!all.f_space && !all.f_plus && !all.dot) ||
			all.currency == (intmax_t)ft_strlen(src)) ||
			(!all.f_zero && all.f_plus &&
			(!all.dot || (all.width > all.currency && all.f_minus)))))
	{
		src = ft_strjoin(" ", src);
		src[0] = sign;
		free(temp);
	}
	else if (all.f_plus || ((all.f_space) && !all.dot))
		src = ft_putusign(src, sign, all);
	return (src);
}

char		*ft_get_unsigned(t_all_flags all, va_list list)
{
	char		*num;
	uintmax_t	sig;

	all.f_plus = 0;
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
		return (ft_numustr_make(ft_itoa_base(va_arg(list, size_t),
			10, all), all));
	else
		sig = va_arg(list, unsigned int);
	num = ft_itoa_base(sig, 10, all);
	return (ft_numustr_make(num, all));
}

char		*ft_get_unsigned_any(char **f, t_all_flags all, va_list list)
{
	if (**f == 'U' && (!all.ll && !all.j && !all.z) && ft_size_flags_null(&all))
	{
		all.l = 1;
		(*f)++;
		return (ft_get_unsigned(all, list));
	}
	(*f)++;
	return (ft_get_unsigned(all, list));
}
