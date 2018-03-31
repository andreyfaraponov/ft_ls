/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_part_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:51:30 by afarapon          #+#    #+#             */
/*   Updated: 2018/03/31 10:33:10 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				ft_all_strcmp(char *s1, char *s2)
{
	size_t		i;
	char		*r1;
	char		*r2;
	size_t		len;
	int			res;

	i = -1;
	r1 = ft_strdup(s1);
	r2 = ft_strdup(s2);
	len = ft_strlen(r1);
	while (++i < len)
		if (r1[i] >= 'A' && r1[i] <= 'Z')
			r1[i] = ft_tolower(r1[i]);
	i = -1;
	len = ft_strlen(r2);
	while (++i < len)
		if (r2[i] >= 'A' && r2[i] <= 'Z')
			r2[i] = ft_tolower(r2[i]);
	res = ft_strcmp(r1, r2);
	free(r1);
	free(r2);
	return (res);
}

void			sort_by_name_array(t_info *arr, unsigned int size)
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
			if (ft_all_strcmp(arr[i].name, arr[j].name) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

void			sort_args(t_localinfo *local)
{
	sort_by_name_array(local->files, local->files_size);
}

static void		files_print(t_info file, t_flags *fl, t_localinfo *local)
{
	if (!S_ISDIR(file.f_stat.st_mode))
	{
		if (fl->f_list)
			print_l_info(local, file.f_stat,
				file.name, local->loc_path);
		else
		{
			printf_file_name(&local->flags, file.f_stat,
				file.name);
			ft_printf("\t");
		}
	}
}

void			directories_print(t_info file, t_flags *fl, t_localinfo *local)
{
	if (S_ISDIR(file.f_stat.st_mode))
	{
		ft_printf("Dir %s\n", file.name);
		open_and_print_dir(file.name, fl, local->files_size == 1 ? 1 : 0);
	}
}

static int		check_for_files(t_localinfo *l)
{
	size_t		i;

	i = -1;
	while (++i < l->files_size)
		if (!S_ISDIR(l->files[i].f_stat.st_mode))
			return (1);
	return (0);
}

void			run_ls_att(t_localinfo *local)
{
	size_t		i;

	i = -1;
	sort_args(local);
	print_errors(local->errors);
	free(local->errors);
	while (++i < local->files_size)
		files_print(local->files[i], &local->flags, local);
	if (!local->flags.f_list && check_for_files(local))
		ft_printf("\n");
	i = -1;
	while (++i < local->files_size)
		directories_print(local->files[i], &local->flags, local);
	free(local->loc_path);
	free(local->files);
}
