/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_part_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:51:30 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/02 00:15:25 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			files_print(t_info file, t_flags *fl, t_localinfo *local)
{
	if (S_ISDIR(file.f_stat.st_mode))
		return ;
	if (fl->f_list)
		print_l_info(local, file.f_stat,
			file.name, local->loc_path);
	else
		printf_file_name(&local->flags, file.f_stat,
			file.name);
}

static int			check_for_files(t_localinfo *l)
{
	size_t		i;

	i = -1;
	while (++i < l->files_size)
		if (!S_ISDIR(l->files[i].f_stat.st_mode))
			return (1);
	return (0);
}

static int			is_any_dir(t_info *arr, int size)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (i < size)
	{
		if (S_ISDIR(arr[i].f_stat.st_mode))
			count++;
		i++;
	}
	if (count == size)
		return (0);
	return (count);
}

static void			run_ls_dirs(t_localinfo *local, unsigned int i)
{
	while (++i < local->files_size)
	{
		if (S_ISDIR(local->files[i].f_stat.st_mode) &&
			!local->flags.f_just_dir)
		{
			ft_printf("%s", i > 0 ? "\n" : "");
			open_and_print_dir(local->files[i], &local->flags);
		}
		else if (S_ISDIR(local->files[i].f_stat.st_mode) &&
			local->flags.f_just_dir)
		{
			if (local->flags.f_list)
				print_l_info(local, local->files[i].f_stat,
					local->files[i].name, local->files[i].full_path);
			else
			{
				printf_file_name(&local->flags,
					local->files[i].f_stat, local->files[i].name);
				ft_printf("%s", i < local->files_size ? "  " : "");
			}
		}
		free(local->files[i].name);
		free(local->files[i].full_path);
	}
}

void			run_ls(t_localinfo *local)
{
	unsigned int	i;

	i = -1;
	sort_args(local);
	if (local->files_size == 1 && !local->flags.f_recur)
		local->flags.no_name = 1;
	print_errors(local->errors);
	free(local->errors);
	while (++i < local->files_size)
	{
		files_print(local->files[i], &local->flags, local);
		ft_printf("%s", (i + 1) == local->files_size ||
			local->flags.f_list ? "" : "  ");
	}
	if ((!local->flags.f_list && check_for_files(local)) ||
		is_any_dir(local->files, local->files_size))
		ft_printf("\n");
	run_ls_dirs(local, -1);
	free(local->loc_path);
	free(local->files);
}
