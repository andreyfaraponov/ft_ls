/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_part_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:51:30 by afarapon          #+#    #+#             */
/*   Updated: 2018/03/31 09:52:42 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				ft_all_strcmp(char *s1, char *s2)
{
	size_t		i;
	char		r1[NAME_SIZE];
	char		r2[NAME_SIZE];

	i = -1;
	while (++i < NAME_SIZE)
		if (s1[i] >= 'A' && s1[i] <= 'Z')
			r1[i] = ft_tolower(s1[i]);
		else
			r1[i] = s1[i];
	r1[i] = '\0';
	i = -1;
	while (++i < NAME_SIZE)
		if (s2[i] >= 'A' && s2[i] <= 'Z')
			r2[i] = ft_tolower(s2[i]);
		else
			r2[i] = s2[i];
	r2[i] = '\0';
	return (ft_strcmp(r1, r2));
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

static void		directories_print(t_info file, t_flags *fl, t_localinfo *local)
{
	if (S_ISDIR(file.f_stat.st_mode))
		open_and_print_dir(file.name, fl);
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
	{
		if (i > 0)
			ft_printf("\n");
		if (local->files_size != 1)
			ft_printf(COLOR_RESET "%s:\n", local->files[i].name);
		directories_print(local->files[i], &local->flags, local);
	}
	free(local->loc_path);
	free(local->files);
}
