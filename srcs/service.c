/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 01:14:15 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/02 00:26:56 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ft_free_strsplit(char **split)
{
	size_t		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

size_t			get_digit_len(size_t val)
{
	size_t		res;

	res = 1;
	while (val / 10)
	{
		val /= 10;
		res++;
	}
	return (res);

}

void			clear_t_localinfo(t_localinfo *info)
{
	size_t		i;

	i = -1;
	while (++i < info->files_size)
	{
		free(info->files[i].full_path);
		free(info->files[i].name);
	}
	free(info->files);
}

void			get_width_for_l(t_localinfo *l)
{
	unsigned int	i;
	struct passwd	*u_name;
	struct group	*g_name;

	i = 0;
	while (i < l->files_size)
	{
		u_name = getpwuid(l->files[i].f_stat.st_uid);
		g_name = getgrgid(l->files[i].f_stat.st_gid);
		if (l->offsets[0] < get_digit_len(l->files[i].f_stat.st_nlink))
			l->offsets[0] = get_digit_len(l->files[i].f_stat.st_nlink);
		if (l->offsets[1] < ft_strlen(u_name->pw_name))
			l->offsets[1] = ft_strlen(u_name->pw_name);
		if (l->offsets[2] < ft_strlen(g_name->gr_name))
			l->offsets[2] = ft_strlen(g_name->gr_name);
		if (l->offsets[3] < get_digit_len(l->files[i].f_stat.st_size))
			l->offsets[3] = get_digit_len(l->files[i].f_stat.st_size);
		i++;
	}
}

void			printf_file_name(t_flags *fl, struct stat s, char *fname)
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

