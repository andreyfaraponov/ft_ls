/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:50:25 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/02 00:39:15 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			print_l_time(struct stat s, int time_flag)
{
	char		*tmp_time;
	char		*ttt;
	char		**split;
	char		**split2;
	time_t		cur_time;

	time(&cur_time);
	time_flag = MY_ABS(cur_time - s.st_mtime) >= 15552000 ? 1 : 0;
	tmp_time = ctime(&s.st_mtime);
	split = ft_strsplit(tmp_time, ' ');
	ft_printf("%3s %2s ", split[1], split[2]);
	if (!time_flag)
	{
		split2 = ft_strsplit(split[3], ':');
		ft_printf("%2s:%2s ", split2[0], split2[1]);
		ft_free_strsplit(split2);
	}
	else
	{
		ttt = ft_strtrim(split[4]);
		ft_printf("%5s ", ttt);
		free(ttt);
	}
	ft_free_strsplit(split);
}

static void			add_link_postfix(t_flags *fl, char *fname, char *path)
{
	char			*full_path;
	char			buf[NAME_SIZE];
	ssize_t			len;

	ft_printf(COLOR_RESET " -> ");
	full_path = ft_strnew(ft_strlen(fname) + ft_strlen(path) + 1);
	ft_strcat(full_path, path);
	if (full_path[ft_strlen(full_path) - 1] != '/')
		ft_strcat(full_path, "/");
	ft_strcat(full_path, fname);
	ft_bzero(buf, NAME_SIZE);
	len = readlink(full_path, buf, NAME_SIZE);
	buf[len] = '\0';
	if (fl->f_colors)
	{
		ft_printf(COLOR_MAGENTA "%s", buf);
		ft_printf(COLOR_RESET);
	}
	else
		ft_printf("%s", buf);
	free(full_path);
}

static int			check_link(char *fname, char *path)
{
	char			*full_path;
	char			buf[NAME_SIZE];
	ssize_t			len;

	ft_printf(COLOR_RESET);
	full_path = ft_strnew(ft_strlen(fname) + ft_strlen(path) + 1);
	ft_strcat(full_path, path);
	if (full_path[ft_strlen(full_path) - 1] != '/')
		ft_strcat(full_path, "/");
	ft_strcat(full_path, fname);
	ft_bzero(buf, NAME_SIZE);
	len = readlink(full_path, buf, NAME_SIZE);
	if (len == -1)
		make_link_error(full_path);
	free(full_path);
	if (len == -1)
		return (1);
	return (0);
}

void				print_l_info(t_localinfo *l, struct stat s,
	char *fname, char *path)
{
	struct passwd	*u_name;
	struct group	*g_name;
	int				flag;

	if (l->flags.f_colors)
		ft_printf(COLOR_RESET);
	flag = S_ISLNK(s.st_mode) && check_link(fname, path) ? 1 : 0;
	print_permissions(s);
	u_name = getpwuid(s.st_uid);
	g_name = getgrgid(s.st_gid);
	ft_printf("%*u ", l->offsets[0] + 2, s.st_nlink);
	if (!l->flags.f_list_not_owner)
		ft_printf("%*s ", l->offsets[1], u_name->pw_name);
	ft_printf("%*s ", l->offsets[2] + 1, g_name->gr_name);
	if (S_ISBLK(s.st_mode) || S_ISCHR(s.st_mode))
		ft_printf("%*u, %*u ",  l->offsets[3] + 1, s.st_rdev >> 24 & 0xff,
			l->offsets[3] + 1, s.st_rdev & 0xffffff);
	else
		ft_printf("%*u ", l->offsets[3] + 1, s.st_size);
	print_l_time(s, l->flags.f_sort_by_mod_time);
	printf_file_name(&l->flags, s, fname);
	if (!flag && S_ISLNK(s.st_mode))
		add_link_postfix(&l->flags, fname, path);
	ft_printf("\n");
}
