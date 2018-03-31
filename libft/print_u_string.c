/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 14:28:56 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/08 13:48:52 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static char	*ft_u_save_large(unsigned int chr, char *src, t_all_flags *all)
{
	char	*res;

	res = ft_strcharjoin(src, M3_ONE(chr));
	res = ft_strcharjoin(res, M3_TWO(chr));
	res = ft_strcharjoin(res, M2_TWO(chr));
	res = ft_strcharjoin(res, M1_TWO(chr));
	all->currency -= 4;
	free(src);
	return (res);
}

static char	*ft_unicode_save(unsigned int chr, char *src, t_all_flags *all)
{
	char				*res;

	res = 0;
	if ((ft_max_bit_size(chr) < 8 || MB_CUR_MAX == 1) &&
		(all->currency >= 1 || !all->dot))
	{
		all->currency--;
		return (ft_strcharjoin(src, chr));
	}
	else if (ft_max_bit_size(chr) < 12 && (all->currency >= 2 || !all->dot))
	{
		res = ft_strcharjoin(ft_strcharjoin(src, M1_ONE(chr)), M1_TWO(chr));
		all->currency -= 2;
	}
	else if (ft_max_bit_size(chr) < 17 && (all->currency >= 3 || !all->dot))
	{
		res = ft_strcharjoin(src, M2_ONE(chr));
		res = ft_strcharjoin(res, M2_TWO(chr));
		res = ft_strcharjoin(res, M1_TWO(chr));
		all->currency -= 3;
	}
	else if (ft_max_bit_size(chr) < 22 && (all->currency >= 4 || !all->dot))
		res = ft_u_save_large(chr, src, all);
	return (res ? res : ft_strdup(""));
}

char		*ft_create_ustring(unsigned int *arr, char *src, t_all_flags *all)
{
	while (*arr != 0)
	{
		src = ft_unicode_save(*arr, src, all);
		arr++;
		if (all->dot && !all->currency)
			break ;
	}
	return (src);
}
