/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 21:32:41 by afarapon          #+#    #+#             */
/*   Updated: 2018/03/31 09:18:17 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				check_errors(int first, int all, char **av, t_localinfo *local)
{
	int		res;
	char	*f_free;
	STAT	tmp;

	res = 0;
	while (first < all)
	{
		if (av[first][0] == '-')
		{
			res++;
			first++;
			continue ;
		}
		if (stat(av[first], &tmp))
		{
			make_error(av[first], local);
			res++;
		}
		first++;
	}
	return (res);
}

void			make_args(int c, char **av, t_localinfo *local, t_flags *fl)
{
	size_t		i;
	size_t		j;
	STAT		tmp;
	char		buf[NAME_SIZE];

	local->flags = *fl;
	local->errors = ft_strdup("");
	local->files_size = c - 1;
	local->files_size -= check_errors(1, c, av, local);
	local->files = (t_info*)malloc(sizeof(t_info) * (local->files_size));
	i = 0;
	j = 0;
	local->loc_path = ft_strdup("./");
	while (++i < c)
	{
		if (lstat(av[i], &tmp))
			continue ;
		else
		{
			local->files[j].f_stat = tmp;
			ft_strcpy(local->files[j].name, av[i]);
			j++;
		}
	}
}

void			get_width_for_l(t_localinfo *l)
{
	size_t			i;
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

int				check_args(int c, char **av)
{
	size_t		i;

	i = 0;
	while (++i < c)
	{
		if (av[i][0] != '-' && ft_strcmp(av[i], "."))
			return (1);
	}
	return (0);
}

void			start_with_att(int c, char **av, t_flags *fl)
{
	t_localinfo		l;

	ft_bzero(&l, sizeof(t_localinfo));
	make_args(c, av, &l, fl);
	if (fl->f_list && !fl->f_dis_lsg)
		get_width_for_l(&l);
	run_ls_att(&l);
}

void			without_att(int c, char **av, t_flags *fl)
{
	t_localinfo		l;

	ft_bzero(&l, sizeof(t_localinfo));
	ft_get_lsflags(fl, c, av);
}

int				main(int c,char **av)
{
	t_flags		fl;

	ft_bzero(&fl, sizeof(t_flags));
	ft_get_lsflags(&fl, c, av);
	if (check_args(c, av))
		start_with_att(c, av, &fl);
	else
		without_att(c, av, &fl);
	return (0);
}
