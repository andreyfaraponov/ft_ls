/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_part_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:51:30 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/01 15:17:04 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

// int				ft_all_strcmp(char *s1, char *s2)
// {
// 	size_t		i;
// 	char		*r1;
// 	char		*r2;
// 	size_t		len;
// 	int			res;

// 	i = -1;
// 	r1 = ft_strdup(s1);
// 	r2 = ft_strdup(s2);
// 	len = ft_strlen(r1);
// 	while (++i < len)
// 		if (r1[i] >= 'A' && r1[i] <= 'Z')
// 			r1[i] = ft_tolower(r1[i]);
// 	i = -1;
// 	len = ft_strlen(r2);
// 	while (++i < len)
// 		if (r2[i] >= 'A' && r2[i] <= 'Z')
// 			r2[i] = ft_tolower(r2[i]);
// 	res = ft_strcmp(r1, r2);
// 	free(r1);
// 	free(r2);
// 	return (res);
// }

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
			if (ft_strcmp(arr[i].name, arr[j].name) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

void			sort_by_mtime(t_info *arr, unsigned int size)
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

void			reverse_args(t_info *arr, unsigned int size)
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

static void		files_print(t_info file, t_flags *fl, t_localinfo *local)
{
	if (!S_ISDIR(file.f_stat.st_mode))
	{
		if (fl->f_list)
			print_l_info(local, file.f_stat,
				file.name, local->loc_path);
		else
			printf_file_name(&local->flags, file.f_stat,
				file.name);
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

int				is_any_dir(t_info *arr, int size)
{
	size_t		i;
	size_t		count;

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
	while (i < size)
	{
		if (S_ISDIR(arr[i].f_stat.st_mode))
			return (1);
		i++;
	}
	return (0);
}

void			run_ls_att(t_localinfo *local)
{
	size_t		i;

	i = -1;
	sort_args(local);
	if (local->files_size == 1 && !local->flags.f_recur)
		local->flags.no_name = 1;
	print_errors(local->errors);
	if (ft_strlen(local->errors) && local->files_size)
		ft_printf("\n%s:\n", local->loc_path);
	free(local->errors);
	while (++i < local->files_size)
	{
		files_print(local->files[i], &local->flags, local);
		ft_printf("%s", (i + 1) == local->files_size ? "" : "  ");
	}
	if ((!local->flags.f_list && check_for_files(local)) || is_any_dir(local->files, local->files_size))
		ft_printf("\n");
	i = -1;
	while (++i < local->files_size)
	{
		if (S_ISDIR(local->files[i].f_stat.st_mode) && !local->flags.f_just_dir)
		{
			if (i > 0)
				ft_printf("\n");
			open_and_print_dir(local->files[i], &local->flags, local->files_size == 1 && !ft_strlen(local->errors) ? 1 : 0);
		}
		else if (S_ISDIR(local->files[i].f_stat.st_mode) && local->flags.f_just_dir)
		{
			if (local->flags.f_list)
				print_l_info(local, local->files[i].f_stat, local->files[i].name, local->files[i].full_path);
			else
			{
				printf_file_name(&local->flags, local->files[i].f_stat, local->files[i].name);
				ft_printf("%s", i < local->files_size ? "  " : "");
			}
		}
		free(local->files[i].name);
		free(local->files[i].full_path);
	}
	free(local->loc_path);
	free(local->files);
}
