/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 01:14:15 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/01 13:22:06 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ft_free_strsplit(char **split)
{
	size_t		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

size_t			get_digit_len(size_t val)
{
	size_t		res;

	res = 1;
	while (val / 10)
	{
		val /= 10;
		res++;
	}
	return (res);

}

void			clear_t_localinfo(t_localinfo *info)
{
	size_t		i;

	i = -1;
	while (++i < info->files_size)
	{
		free(info->files[i].full_path);
		free(info->files[i].name);
	}
	free(info->files);
}