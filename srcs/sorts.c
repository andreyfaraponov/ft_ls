/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 23:00:21 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/01 23:01:15 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		sort_by_name_array(t_info *arr, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	t_info			tmp;

	i = -1;
	while (++i < size)
	{
		j = i;
		while (++j < size)
		{
			if (ft_strcmp(arr[i].name, arr[j].name) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

static void		sort_by_mtime(t_info *arr, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	t_info			tmp;

	i = -1;
	while (++i < size)
	{
		j = i;
		while (++j < size)
			if (arr[i].f_stat.st_mtime < arr[j].f_stat.st_mtime)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			else if (arr[i].f_stat.st_mtime == arr[j].f_stat.st_mtime &&
				ft_strcmp(arr[i].name, arr[j].name) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
	}
}

static void		reverse_args(t_info *arr, unsigned int size)
{
	size_t		i;
	t_info		tmp;

	i = 0;
	while (i < --size)
	{
		tmp = arr[i];
		arr[i] = arr[size];
		arr[size] = tmp;
		i++;
	}
}

void			sort_args(t_localinfo *local)
{
	if (!local->flags.f_dis_lsg)
	{
		sort_by_name_array(local->files, local->files_size);
		if (local->flags.f_by_time)
			sort_by_mtime(local->files, local->files_size);
	}
	if (local->flags.f_rever && local->files_size)
		reverse_args(local->files, local->files_size);
}
