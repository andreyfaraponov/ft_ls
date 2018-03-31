/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 21:32:41 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/01 01:02:38 by afarapon         ###   ########.fr       */
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
		if (lstat(av[first], &tmp))
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

	local->flags = *fl;
	local->errors = ft_strdup("");
	local->files_size = c - 1;
	local->files_size -= check_errors(1, c, av, local);
	local->files = (t_info*)malloc(sizeof(t_info) * (local->files_size > 0 ? local->files_size : 1));
	i = 0;
	j = 0;
	local->loc_path = ft_strdup("");
	while (++i < c)
	{
		if (lstat(av[i], &tmp))
			continue ;
		else
		{
			local->files[j].f_stat = tmp;
			local->files[j].name = ft_strdup(av[i]);
			local->files[j].full_path = ft_strdup(av[i]);
			j++;
		}
	}
	if ((c == 1 || !local->files_size) && !ft_strlen(local->errors))
	{
		// ft_printf("res: %d\n", lstat(".", &tmp));
		lstat(".", &tmp);
		local->files[0].f_stat = tmp;
		local->files[0].name = ft_strdup(".");
		local->files[0].full_path = ft_strdup(".");
		local->files_size = 1;
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

void			first_start(int c, char **av, t_flags *fl)
{
	t_localinfo		l;

	ft_bzero(&l, sizeof(t_localinfo));
	make_args(c, av, &l, fl);
	if (fl->f_list && !fl->f_dis_lsg)
		get_width_for_l(&l);
	run_ls_att(&l);
}

int				main(int c,char **av)
{
	t_flags		fl;

	ft_bzero(&fl, sizeof(t_flags));
	ft_get_lsflags(&fl, c, av);
	first_start(c, av, &fl);
	return (0);
}
