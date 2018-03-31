/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 21:32:32 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/08 12:36:28 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_all_flags_init(t_all_flags *flags)
{
	ft_memset(flags, 0, sizeof(t_all_flags));
}

static char	ft_get_numchar(uintmax_t n, char sys, char isupper)
{
	char	*str;

	if (isupper)
		str = "0123456789ABCDEF";
	else
		str = "0123456789abcdef";
	return (str[n % sys]);
}

char		*ft_itoa_base(size_t num, char system, t_all_flags all)
{
	size_t		count;
	char		*result;
	size_t		temp;

	temp = num;
	count = 0;
	if (num == 0)
		return (ft_strdup("0"));
	while (num != 0)
	{
		count++;
		num /= system;
	}
	result = (char*)malloc(sizeof(char) * (count + 1));
	result[count--] = '\0';
	while (temp > 0)
	{
		result[count--] = ft_get_numchar(temp, system, all.large);
		temp /= system;
	}
	return (result);
}

char		*ft_get_oct_sign(t_all_flags all)
{
	char	*res;

	res = 0;
	if (all.f_sharp)
		res = ft_strdup("0");
	return (res);
}

char		ft_get_sign(t_all_flags all, int isneg)
{
	char	sign;

	if (isneg)
		sign = '-';
	else if (all.f_plus)
		sign = '+';
	else if (all.f_space)
		sign = ' ';
	else
		sign = 0;
	return (sign);
}
