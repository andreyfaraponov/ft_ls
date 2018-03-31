/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 21:34:28 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/08 12:36:01 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_help_one(char *src, t_all_flags all, char *sign)
{
	char	*temp;

	if (all.f_minus || !all.f_zero)
	{
		temp = src;
		src = ft_strjoin(sign, src);
		src = ft_make_width(src, all);
	}
	else
	{
		all.width = all.width - 2;
		src = ft_make_width(src, all);
		temp = src;
		src = ft_strjoin(sign, src);
	}
	free(temp);
	free(sign);
	return (src);
}

static char	*ft_help_two(char *src, t_all_flags all, char *sign, int cmp)
{
	char	*temp;

	src = ft_make_precision(src, all);
	if (!cmp && sign && !all.dot &&
		((int)(ft_strlen(src) + 2) >= all.width || !all.f_zero))
	{
		temp = src;
		src = ft_strjoin(sign, src);
		free(temp);
	}
	else if (!cmp && all.dot)
	{
		free(src);
		src = ft_strjoin(sign, "");
	}
	else if (!cmp && sign && !all.dot && all.width)
	{
		src = ft_make_width(src, all);
		src[1] = 'x';
	}
	if (sign)
		free(sign);
	src = ft_make_width(src, all);
	return (src);
}

static char	*ft_memory_make(char *src, t_all_flags all, int cmp)
{
	char	*sign;

	sign = ft_get_hex_sign(all);
	if (sign && cmp)
		src = ft_help_one(src, all, sign);
	else if (!cmp && all.dot && !all.f_sharp)
	{
		free(src);
		src = ft_strdup("");
		src = ft_make_width(src, all);
	}
	else
		src = ft_help_two(src, all, sign, cmp);
	return (src);
}

char		*ft_print_memory(char **f, t_all_flags all_flags, va_list list)
{
	char				*res;
	unsigned long int	ptr;

	(*f)++;
	all_flags.f_sharp = 1;
	all_flags.large = 0;
	ptr = va_arg(list, unsigned long int);
	res = ft_itoa_base(ptr, 16, all_flags);
	res = ft_make_precision(res, all_flags);
	res = ft_memory_make(res, all_flags, ft_strcmp("0", res));
	return (res);
}
