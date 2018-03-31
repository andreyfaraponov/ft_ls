/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 21:20:53 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/08 12:36:38 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_print_nums(char **f, t_all_flags all_flags, va_list list)
{
	char		*str_num;

	str_num = "";
	if ((**f == 'd' || **f == 'i') && (*f)++)
		str_num = ft_get_int(all_flags, list);
	else if (**f == 'D' && (*f)++)
		str_num = ft_get_lint(all_flags, list);
	else if (**f == 'o' || **f == 'O')
		str_num = ft_get_oct_any(f, all_flags, list, 8);
	else if (**f == 'u' || **f == 'U')
		str_num = ft_get_unsigned_any(f, all_flags, list);
	else if (**f == 'x' || **f == 'X')
		str_num = ft_get_hex_any(f, all_flags, list, 16);
	return (str_num);
}

char		*ft_make_width(char *src, t_all_flags all)
{
	char		sign;
	ssize_t		len;
	char		*result;
	char		*width;

	len = (int)ft_strlen(src);
	if (len >= all.width)
		return (src);
	if (all.f_minus)
		sign = ' ';
	else
		sign = (char)(all.f_zero == 1 ? '0' : ' ');
	len = all.width - ft_strlen(src);
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

char		*ft_make_precision(char *src, t_all_flags all)
{
	intmax_t	len;
	char		*result;
	char		*zeros;

	len = ft_strlen(src);
	if (len >= all.currency)
		return (src);
	zeros = ft_strnew((size_t)all.currency - len);
	zeros = (char*)ft_memset(zeros, '0', (size_t)(all.currency - len));
	result = ft_strjoin(zeros, src);
	free(zeros);
	free(src);
	return (result);
}

char		*ft_get_hex_sign(t_all_flags all)
{
	char		*res;

	res = 0;
	if (all.f_sharp)
	{
		if (all.large)
			res = ft_strdup("0X");
		else
			res = ft_strdup("0x");
	}
	return (res);
}

char		*ft_putsign(char *src, char sign, t_all_flags all, int isneg)
{
	char		*temp;
	char		*str_sign;

	temp = src;
	if (*src == ' ' && sign != ' ')
	{
		while (*src == ' ')
			src++;
		*(src - 1) = sign;
	}
	else if ((sign == '+' || sign == '-') && *src == '0')
		*src = sign;
	else if (!all.dot || isneg || all.f_plus)
	{
		str_sign = ft_strnew(1);
		str_sign[0] = sign;
		temp = ft_strjoin(str_sign, src);
		free(src);
		free(str_sign);
	}
	return (temp);
}
