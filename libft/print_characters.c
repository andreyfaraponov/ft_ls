/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 21:27:56 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/08 12:36:37 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_print_null(char chr, t_all_flags all_flags)
{
	char	*res;
	int		counter;

	counter = 1;
	all_flags.width--;
	if (all_flags.f_minus)
	{
		write(1, &chr, 1);
		res = ft_make_width_char(ft_strnew(1), all_flags);
		counter += (int)write(1, res, ft_strlen(res));
	}
	else
	{
		res = ft_make_width_char(ft_strnew(1), all_flags);
		counter += (int)write(1, res, ft_strlen(res));
		write(1, &chr, 1);
	}
	free(res);
	return (counter);
}

int			ft_print_characters(char **f, t_all_flags all_flags, va_list list)
{
	int		chr;
	char	*res;
	int		result;

	if (**f == 'C' && MB_CUR_MAX == 4)
		return (ft_print_u_characters(f, all_flags, list));
	chr = va_arg(list, int);
	(*f)++;
	if (chr)
	{
		res = ft_strnew(1);
		res[0] = (char)chr;
		res = ft_make_width_char(res, all_flags);
		result = (int)write(1, res, ft_strlen(res));
		free(res);
		return (result);
	}
	else
		result = ft_print_null((char)chr, all_flags);
	return (result);
}

char		*ft_make_width_char(char *src, t_all_flags all)
{
	wchar_t		sign;
	intmax_t	len;
	char		*result;
	char		*width;

	len = (int)ft_strlen(src);
	if (len >= all.width)
		return (src);
	if (all.f_minus)
		sign = ' ';
	else
		sign = (char)(all.f_zero == 1 ? '0' : ' ');
	len = all.width - (int)ft_strlen(src);
	width = ft_strnew((size_t)len);
	if (len > 0 && width)
		ft_memset(width, sign, (size_t)len);
	if (all.f_minus)
		result = ft_strjoin(src, width);
	else
		result = ft_strjoin(width, src);
	free(src);
	free(width);
	return (result);
}
