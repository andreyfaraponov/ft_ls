/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 22:25:05 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/08 12:36:05 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_make_width_octet(char *src, t_all_flags all)
{
	char		sign;
	intmax_t	len;
	char		*result;
	char		*width;

	len = ft_strlen(src);
	if (len >= all.width && len >= all.currency)
		return (src);
	if (all.f_minus)
		sign = ' ';
	else
		sign = (char)(all.f_zero == 1 ? '0' : ' ');
	len = all.width - (int)ft_strlen(src);
	width = ft_strnew((size_t)len);
	if (len > 0 && width)
		width = ft_memset(width, sign, (size_t)len);
	if (all.f_minus)
		result = ft_strjoin(src, width);
	else
		result = ft_strjoin(width, src);
	free(width);
	free(src);
	return (result);
}

char		*ft_get_oct(t_all_flags all, va_list list, char system)
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
		sig = va_arg(list, size_t);
	else
		sig = va_arg(list, unsigned int);
	num = ft_itoa_base(sig, system, all);
	return (ft_oct_make(num, all));
}

char		*ft_get_oct_any(char **f, t_all_flags all, va_list list,
	char system)
{
	if (**f == 'O' && (!all.ll && !all.j && !all.z) &&
		ft_size_flags_null(&all))
		all.l = 1;
	(*f)++;
	return (ft_get_oct(all, list, system));
}

static char	*ft_helper_three(char *src, t_all_flags all, char *sign)
{
	char	*temp;

	if (all.f_minus || !all.f_zero)
	{
		temp = src;
		src = ft_strjoin(sign, src);
		src = ft_make_precision(src, all);
		src = ft_make_width_octet(src, all);
	}
	else
	{
		all.width = all.width - 1;
		src = ft_make_width_octet(src, all);
		temp = src;
		src = ft_strjoin(sign, src);
		src = ft_make_precision(src, all);
	}
	free(temp);
	return (src);
}

char		*ft_oct_make(char *src, t_all_flags all)
{
	char	*sign;

	sign = ft_get_oct_sign(all);
	if (all.dot)
		all.f_zero = 0;
	if (!ft_strcmp("0", src) && (all.dot || all.currency || all.width))
	{
		free(src);
		src = ft_strnew(0);
	}
	if (sign && ft_strcmp("0", src))
		src = ft_helper_three(src, all, sign);
	else
	{
		src = ft_make_precision(src, all);
		src = ft_make_width_octet(src, all);
	}
	if (all.f_sharp)
		free(sign);
	return (src);
}
