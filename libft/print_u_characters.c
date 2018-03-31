/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u_characters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 22:15:52 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/08 12:36:17 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_max_bit_size(unsigned int n)
{
	int size;

	size = 0;
	while (n)
	{
		n >>= 1;
		size++;
	}
	return (size);
}

static char	*ft_strcharjoin(char *s1, unsigned char chr)
{
	char	*temp_one;
	char	*result;

	temp_one = ft_strnew(1);
	ft_memset(temp_one, chr, 1);
	result = ft_strjoin(s1, temp_one);
	free(temp_one);
	free(s1);
	return (result);
}

static char	*ft_u_save_large(unsigned int chr, char *src)
{
	char	*res;

	res = ft_strcharjoin(src, M3_ONE(chr));
	res = ft_strcharjoin(res, M3_TWO(chr));
	res = ft_strcharjoin(res, M2_TWO(chr));
	res = ft_strcharjoin(res, M1_TWO(chr));
	free(src);
	return (res);
}

static char	*ft_unicode_save(unsigned int chr, char *src)
{
	char				*res;

	res = 0;
	if (ft_max_bit_size(chr) < 8)
		res = ft_strcharjoin(src, chr);
	else if (ft_max_bit_size(chr) < 12)
		res = ft_strcharjoin(ft_strcharjoin(src, M1_ONE(chr)), M1_TWO(chr));
	else if (ft_max_bit_size(chr) < 17)
	{
		res = ft_strcharjoin(src, M2_ONE(chr));
		res = ft_strcharjoin(res, M2_TWO(chr));
		res = ft_strcharjoin(res, M1_TWO(chr));
	}
	else if (ft_max_bit_size(chr) < 22)
		res = ft_u_save_large(chr, src);
	return (res ? res : ft_strdup(""));
}

int			ft_print_u_characters(char **f, t_all_flags all_flags, va_list list)
{
	unsigned int	chr;
	char			*res;
	int				counter;

	chr = va_arg(list, unsigned int);
	(*f)++;
	if (chr)
	{
		res = ft_make_width_char(ft_unicode_save(chr, ft_strnew(0)), all_flags);
		counter = (int)write(1, res, ft_strlen(res));
		free(res);
	}
	else
		counter = ft_print_null((char)chr, all_flags);
	return (counter);
}
