/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:50:25 by afarapon          #+#    #+#             */
/*   Updated: 2018/03/31 09:17:13 by afarapon         ###   ########.fr       */
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
			ft_printf(COLOR_BOLD_CYAN); // OK
		else if (S_ISCHR(s.st_mode))
			ft_printf(COLOR_GREEN);
		else if (S_ISBLK(s.st_mode))
			ft_printf(COLOR_BOLD_GREEN);
		else if (S_ISFIFO(s.st_mode))
			ft_printf(COLOR_YELLOW); // OK
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

static void			draw_permissions(struct stat s)
{
	ft_printf("%s", s.st_mode & S_IRUSR ? "r" : "-");
	ft_printf("%s", s.st_mode & S_IWUSR ? "w" : "-");
	ft_printf("%s", s.st_mode & S_IXUSR ? "x" : "-");
	ft_printf("%s", s.st_mode & S_IRGRP ? "r" : "-");
	ft_printf("%s", s.st_mode & S_IWGRP ? "w" : "-");
	ft_printf("%s", s.st_mode & S_IXGRP ? "x" : "-");
	ft_printf("%s", s.st_mode & S_IROTH ? "r" : "-");
	ft_printf("%s", s.st_mode & S_IWOTH ? "w" : "-");
	ft_printf("%s ", s.st_mode & S_IXOTH ? "x" : "-");
}

void				print_l_time(struct stat s, int time_flag)
{
	char		*tmp_time;
	char		**split;
	char		**split2;
	size_t		cur_time;
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
	char			buf[NAME_SIZE];
	char			buf2[NAME_SIZE * 2];
	ssize_t			len;

	ft_printf(COLOR_RESET " -> ");
	ft_bzero(buf2, NAME_SIZE * 2);
	ft_strcat(buf2, path);
	if (buf2[ft_strlen(buf2) - 1] != '/')
		ft_strcat(buf2, "/");
	ft_strcat(buf2, fname);
	len = readlink(buf2, buf, NAME_SIZE);
	buf[len] = '\0';
	if (fl->f_colors)
	{
		ft_printf(COLOR_MAGENTA "%s", buf);
		ft_printf(COLOR_RESET);
	}
	else
		ft_printf("%s", buf);
}

void			print_l_info(t_localinfo *l, struct stat s, char *fname, char *path)
{
	struct passwd	*u_name;
	struct group	*g_name;

	if (l->flags.f_colors)
		ft_printf(COLOR_RESET);
	file_l_letter(s);
	draw_permissions(s);
	u_name = getpwuid(s.st_uid);
	g_name = getgrgid(s.st_gid);
	ft_printf("%*u ", l->offsets[0], s.st_nlink);
	ft_printf("%*s ", l->offsets[1], u_name->pw_name);
	ft_printf("%*s ", l->offsets[2], g_name->gr_name);
	ft_printf("%*u ", l->offsets[3], s.st_size);
	print_l_time(s, l->flags.f_sort_by_mod_time);
	printf_file_name(&l->flags, s, fname);
	if (S_ISLNK(s.st_mode))
		add_link_postfix(&l->flags, s, fname, path);
	ft_printf("\n");
}
