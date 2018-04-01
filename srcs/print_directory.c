/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 09:05:50 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/01 14:32:16 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			add_argument(t_localinfo *l, char *file, char *full)
{
	size_t		i;
	t_info		*new_arr;
	STAT		tmp;
	t_info		res;

	i = -1;
	if (lstat(full, &tmp) && make_link_error(full))
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

unsigned int	get_total_blocks_size(t_localinfo *l)
{
	unsigned int	res;
	size_t			i;

	res = 0;
	i = -1;
	while (++i < l->files_size)
		res += l->files[i].f_stat.st_blocks;
	return (res);
}

void			open_and_print_dir(t_info file, t_flags *fl, int is_one)
{
	DIR				*dir;
	struct	dirent	*dd;
	t_localinfo		l;
	size_t			i;
	char			*tmp;

	ft_bzero(&l, sizeof(t_localinfo));
	l.flags = *fl;
	dir = opendir(file.full_path);
	if (!dir && make_permission_error(file.full_path))
		return ;
	if (!l.flags.no_name)
		ft_printf(COLOR_RESET "%s:\n", file.full_path);
	while ((dd = readdir(dir)))
	{
		if (dd->d_name[0] == '.' && fl->f_all)
		{
			if (file.full_path[ft_strlen(file.full_path) - 1] != '/')
				tmp = ft_strjoin(file.full_path, "/");
			else
				tmp = file.full_path;
			add_argument(&l, dd->d_name, ft_strjoin(tmp, dd->d_name));
			if (file.name[ft_strlen(file.name) - 1] != '/')
				free(tmp);
		}
		else if (dd->d_name[0] != '.' && ft_strcmp(dd->d_name, ".."))
		{
			if (file.full_path[ft_strlen(file.full_path) - 1] != '/')
				tmp = ft_strjoin(file.full_path, "/");
			else
				tmp = file.full_path;
			add_argument(&l, dd->d_name, ft_strjoin(tmp, dd->d_name));
			if (file.full_path[ft_strlen(file.full_path) - 1] != '/')
				free(tmp);
		}
	}
	closedir(dir);
	sort_args(&l);
	get_width_for_l(&l);
	if (l.flags.f_list && l.files_size)
		ft_printf("total %u\n", get_total_blocks_size(&l));
	i = -1;
	while (++i < l.files_size)
	{
		if (l.flags.f_list)
			print_l_info(&l, l.files[i].f_stat, l.files[i].name, file.full_path);
		else
		{
			printf_file_name(&l.flags, l.files[i].f_stat, l.files[i].name);
			ft_printf("%s", (i + 1) == l.files_size ? "" : "  ");
		}
	}
	if (!l.flags.f_list)
		ft_printf("\n");
	if (l.flags.f_recur)
	{
		i = -1;
		while (++i < l.files_size)
		{
			if (ft_strcmp(".", l.files[i].name) && ft_strcmp("..", l.files[i].name) && S_ISDIR(l.files[i].f_stat.st_mode))
			{

				ft_printf("\n");
				open_and_print_dir(l.files[i], &l.flags, 0);
			}
		}
	}
	clear_t_localinfo(&l);
}
