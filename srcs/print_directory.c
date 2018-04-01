/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 09:05:50 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/02 01:06:22 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void				add_argument(t_localinfo *l, char *file, char *full)
{
	unsigned int	i;
	t_info			*new_arr;
	STAT			tmp;
	t_info			res;

	if ((i = -1) && lstat(full, &tmp) && make_link_error(full))
		return ;
	new_arr = (t_info*)malloc(sizeof(t_info) * (l->files_size + 1));
	while (++i < l->files_size)
		new_arr[i] = l->files[i];
	res.f_stat = tmp;
	res.name = ft_strdup(file);
	res.full_path = full;
	new_arr[i] = res;
	if (l->files_size)
		free(l->files);
	l->files = new_arr;
	l->files_size++;
}

static unsigned int		get_total_blocks_size(t_localinfo *l)
{
	unsigned int	res;
	size_t			i;

	res = 0;
	i = -1;
	while (++i < l->files_size)
		res += l->files[i].f_stat.st_blocks;
	return (res);
}

static void				add_file_from_dir(struct dirent *dd, t_info file,
	t_localinfo *l)
{
	char		*tmp;

	if (dd->d_name[0] == '.' && l->flags.f_all)
	{
		if (file.full_path[ft_strlen(file.full_path) - 1] != '/')
			tmp = ft_strjoin(file.full_path, "/");
		else
			tmp = file.full_path;
		add_argument(l, dd->d_name, ft_strjoin(tmp, dd->d_name));
		if (file.name[ft_strlen(file.name) - 1] != '/')
			free(tmp);
	}
	else if (dd->d_name[0] != '.' && ft_strcmp(dd->d_name, ".."))
	{
		if (file.full_path[ft_strlen(file.full_path) - 1] != '/')
			tmp = ft_strjoin(file.full_path, "/");
		else
			tmp = file.full_path;
		add_argument(l, dd->d_name, ft_strjoin(tmp, dd->d_name));
		if (file.full_path[ft_strlen(file.full_path) - 1] != '/')
			free(tmp);
	}
}

static int				get_all_files_in_dir(t_info file, t_localinfo *l,
	unsigned int i)
{
	DIR				*dir;
	struct	dirent	*dd;

	if (!(dir = opendir(file.full_path)) &&
		make_permission_error(file.full_path))
		return (1);
	if (!l->flags.no_name)
		ft_printf(COLOR_RESET "%s:\n", file.full_path);
	while ((dd = readdir(dir)))
		add_file_from_dir(dd, file, l);
	closedir(dir);
	sort_args(l);
	get_width_for_l(l);
	if (l->flags.f_list && l->files_size)
		ft_printf("total %u\n", get_total_blocks_size(l));
	while (++i < l->files_size)
		if (l->flags.f_list)
			print_l_info(l, l->files[i].f_stat,
				l->files[i].name, file.full_path);
		else
		{
			printf_file_name(&l->flags, l->files[i].f_stat, l->files[i].name);
			ft_printf("%s", (i + 1) == l->files_size ? "" : "  ");
		}
	return (0);
}

void					open_and_print_dir(t_info file, t_flags *fl)
{
	t_localinfo		l;
	size_t			i;

	ft_bzero(&l, sizeof(t_localinfo));
	l.flags = *fl;
	if (get_all_files_in_dir(file, &l, -1))
		return ;
	!l.flags.f_list ? ft_printf("\n") : 0;
	if (l.flags.f_recur && (i = -1))
	{
		while (++i < l.files_size)
		{
			if (ft_strcmp(".", l.files[i].name) && ft_strcmp("..",
				l.files[i].name) && S_ISDIR(l.files[i].f_stat.st_mode))
			{

				ft_printf("\n");
				open_and_print_dir(l.files[i], &l.flags);
			}
		}
	}
	clear_t_localinfo(&l);
}
