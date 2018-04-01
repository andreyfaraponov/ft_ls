/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:50:25 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/01 14:32:49 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void				printf_file_name(t_flags *fl, struct stat s, char *fname)
{
	if (fl->f_colors)
	{
		if (S_ISLNK(s.st_mode))
			ft_printf(COLOR_MAGENTA);
		else if (S_ISDIR(s.st_mode))
			ft_printf(COLOR_BOLD_CYAN);
		else if (S_ISCHR(s.st_mode))
			ft_printf(COLOR_GREEN);
		else if (S_ISBLK(s.st_mode))
			ft_printf(COLOR_BOLD_GREEN);
		else if (S_ISFIFO(s.st_mode))
			ft_printf(COLOR_YELLOW);
		else if (S_ISSOCK(s.st_mode))
			ft_printf(COLOR_BLUE);
	}
	ft_printf("%s", fname);
}

static void			file_l_letter(struct stat s)
{
	if (S_ISLNK(s.st_mode))
		ft_printf("%s", "l");
	else if (S_ISDIR(s.st_mode))
		ft_printf("%s", "d");
	else if (S_ISCHR(s.st_mode))
		ft_printf("%s", "c");
	else if (S_ISBLK(s.st_mode))
		ft_printf("%s", "b");
	else if (S_ISFIFO(s.st_mode))
		ft_printf("%s", "p");
	else if (S_ISSOCK(s.st_mode))
		ft_printf("%s", "s");
	else
		ft_printf("%s", "-");
}

void				draw_user_x(STAT s)
{
	mode_t			st_mode;

	st_mode = s.st_mode;
	if (st_mode & S_IRWXU && st_mode & S_ISUID)
	{
		if (st_mode & S_ISUID && st_mode & S_IXUSR)
			ft_printf("s");
		else if (st_mode & S_ISUID && !(st_mode & S_IXUSR))
			ft_printf("S");
		else
			ft_printf("x");
	}
	else
	{
		if (st_mode & S_IXUSR)
			ft_printf("x");
		else if (st_mode & S_ISUID && st_mode & S_IXUSR)
			ft_printf("s");
		else if (st_mode & S_ISUID && !(st_mode & S_IXUSR))
			ft_printf("S");
		else
			ft_printf("-");
	}
}
void				draw_group_x(STAT s)
{
	mode_t			st_mode;

	st_mode = s.st_mode;
	if (st_mode & S_IRWXG && st_mode & S_ISGID)
	{
		if (st_mode & S_ISGID && st_mode & S_IXGRP)
			ft_printf("s");
		else if (st_mode & S_ISGID && !(st_mode & S_IXGRP))
			ft_printf("S");
		else
			ft_printf("x");
	}
	else
	{
		if (st_mode & S_IXGRP)
			ft_printf("x");
		else if (st_mode & S_ISGID && st_mode & S_IXGRP)
			ft_printf("s");
		else if (st_mode & S_ISGID && !(st_mode & S_IXGRP))
			ft_printf("S");
		else
			ft_printf("-");
	}
}
void				draw_other_x(STAT s)
{
	mode_t			st_mode;

	st_mode = s.st_mode;
	if (st_mode & S_IRWXO && st_mode & S_ISVTX)
	{
		if (st_mode & S_ISVTX && st_mode & S_IXOTH)
			ft_printf("t");
		else if (st_mode & S_ISVTX && !(st_mode & S_IXOTH))
			ft_printf("T");
		else
			ft_printf("x");
	}
	else
	{
		if (st_mode & S_IXOTH)
			ft_printf("x");
		else if (st_mode & S_ISVTX && st_mode & S_IXOTH)
			ft_printf("t");
		else if (st_mode & S_ISVTX && !(st_mode & S_IXOTH))
			ft_printf("T");
		else
			ft_printf("-");
	}
}

static void			draw_permissions(STAT s)
{
	ft_printf("%s", s.st_mode & S_IRUSR ? "r" : "-");
	ft_printf("%s", s.st_mode & S_IWUSR ? "w" : "-");
	draw_user_x(s);
	ft_printf("%s", s.st_mode & S_IRGRP ? "r" : "-");
	ft_printf("%s", s.st_mode & S_IWGRP ? "w" : "-");
	draw_group_x(s);
	ft_printf("%s", s.st_mode & S_IROTH ? "r" : "-");
	ft_printf("%s", s.st_mode & S_IWOTH ? "w" : "-");
	draw_other_x(s);
}

void				print_l_time(struct stat s, int time_flag, t_flags *fl)
{
	char		*tmp_time;
	char		**split;
	char		**split2;
	time_t		cur_time;
	size_t		i;

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
		char	*ttt;
		ttt = ft_strtrim(split[4]);
		ft_printf("%5s ", ttt);
		free(ttt);
	}
	ft_free_strsplit(split);
}

void				add_link_postfix(t_flags *fl, STAT s, char *fname, char *path)
{
	char			*full_path;
	char			buf[NAME_SIZE];
	char			*tmp;
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

int				check_link(t_flags *fl, STAT s, char *fname, char *path)
{
	char			*full_path;
	char			buf[NAME_SIZE];
	char			*tmp;
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

void			print_l_info(t_localinfo *l, struct stat s, char *fname, char *path)
{
	struct passwd	*u_name;
	struct group	*g_name;
	int				flag;

	if (l->flags.f_colors)
		ft_printf(COLOR_RESET);
	if (S_ISLNK(s.st_mode) && check_link(&l->flags, s, fname, path))
		flag = 1;
	else
		flag = 0;
	file_l_letter(s);
	draw_permissions(s);
	u_name = getpwuid(s.st_uid);
	g_name = getgrgid(s.st_gid);
	ft_printf("%*u ", l->offsets[0] + 2, s.st_nlink);
	if (!l->flags.f_list_not_owner)
		ft_printf("%*s ", l->offsets[1], u_name->pw_name);
	ft_printf("%*s ", l->offsets[2] + 1, g_name->gr_name);
	if (S_ISBLK(s.st_mode) || S_ISCHR(s.st_mode))
		ft_printf("%*u, %*u ",  l->offsets[3] + 1, s.st_rdev >> 24 & 0xff,  l->offsets[3] + 1, s.st_rdev & 0xffffff);
	else
		ft_printf("%*u ", l->offsets[3] + 1, s.st_size);
	print_l_time(s, l->flags.f_sort_by_mod_time, &l->flags);
	printf_file_name(&l->flags, s, fname);
	if (!flag && S_ISLNK(s.st_mode))
		add_link_postfix(&l->flags, s, fname, path);
	ft_printf("\n");
}
